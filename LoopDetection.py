from typing import Any, Counter, Dict, Iterator, List, NamedTuple, Optional, Tuple, Union
from typing_extensions import TypedDict

import numpy as np
import torch
from dpu_utils.mlutils import Vocabulary
from torch import nn

from ptgnn.baseneuralmodel import AbstractNeuralModel, ModuleWithMetrics
from ptgnn.baseneuralmodel.utils.data import enforce_not_None
from ptgnn.neuralmodels.gnn import GnnOutput, GraphData, TensorizedGraphData
from ptgnn.neuralmodels.gnn.graphneuralnetwork import GraphNeuralNetwork, GraphNeuralNetworkModel
import networkx as nx

XGraph = TypedDict(
    "XGraph",
    {
        "nodes": nx.classes.reportviews.NodeView,
        "edges": nx.classes.reportviews.EdgeView,
        "result": int,
    },
)

Prediction = Tuple[XGraph, Dict[int,int]]


class TensorizedGraph2ClassSample(NamedTuple):
    graph: XGraph
    supernode_target_classes: int

class Graph2ClassModule(ModuleWithMetrics):
    def __init__(self, gnn: GraphNeuralNetwork,num_target_classes):
        super().__init__()
        self.__gnn = gnn
        self.__node_to_class = nn.Linear(
            in_features=gnn.output_node_state_dim, out_features=2,bias = True
        )
        nn.init.uniform_(self.__node_to_class.weight)
        nn.init.zeros_(self.__node_to_class.bias)
        self.__loss = nn.CrossEntropyLoss()

    def _reset_module_metrics(self) -> None:
        self.__num_samples = 0
        self.__sum_accuracy = 0

    def _module_metrics(self) -> Dict[str, Any]:
        return {"Accuracy": self.__sum_accuracy / self.__num_samples}
    def _logits(self, graph_mb_data):
        graph_output: GnnOutput = self.__gnn(**graph_mb_data)
        #out = nn.Sigmoid()
        return self.__node_to_class(graph_output.output_node_representations[:])
    
    def predict(self, graph_mb_data) -> torch.Tensor:
        with torch.no_grad():
            logits = self._logits(graph_mb_data)
            return logits

    def forward(self, graph_mb_data, target_classes):
        logits = self._logits(graph_mb_data)
        with torch.no_grad():
            for i in range(len(target_classes)):
                if torch.argmax(logits[i]) == target_classes[i]:
                    self.__sum_accuracy +=1
            self.__num_samples += int(target_classes.shape[0])
        return self.__loss(logits, target_classes)

class Graph2Class(
    AbstractNeuralModel[XGraph, TensorizedGraph2ClassSample, Graph2ClassModule]
):
    def __init__(
        self,
        gnn_model: GraphNeuralNetworkModel[str, Any],
        try_simplify_unks: bool = True,
    ):
        super().__init__()
        self.__gnn_model = gnn_model
        self.__try_simplify_unks = try_simplify_unks
        self.__tensorize_samples_with_no_annotation = False
        self.__tensorize_keep_original_supernode_idx = False

    def __convert(self, x_graph: XGraph) -> Tuple[GraphData[int], List[int]]:
        edge_dic = {"first":[]}
        for (u,v) in x_graph["edges"]:
            edge_dic["first"].append((u,v))
            edge_dic["first"].append((v,u))
        edge_dic
        info = np.array([[1,0] for i in list(x_graph["nodes"])])
        info[0] = [0,1]
        return (
            GraphData[str](
                node_information=info,
                edges=edge_dic,
                reference_nodes = {}
            ),
            x_graph["result"],
            
        )

    def build_neural_module(self) -> Graph2ClassModule:
        return Graph2ClassModule(gnn=self.__gnn_model.build_neural_module(), num_target_classes=2)

    def tensorize(self, datapoint: XGraph) -> Optional[TensorizedGraph2ClassSample]:
        graph_data, target_classes = self.__convert(datapoint)
        graph_tensorized_data = self.__gnn_model.tensorize(graph_data)
        if graph_tensorized_data is None:
            print("Something is probably wrong")
            return None  # Sample rejected by the GNN
        return TensorizedGraph2ClassSample(
            graph=graph_tensorized_data, supernode_target_classes=target_classes
        )
    def update_metadata_from(self, datapoint: XGraph) -> None:
        graph_data, target_classes = self.__convert(datapoint)
        self.__gnn_model.update_metadata_from(graph_data)
    # region Minibatching
    def initialize_minibatch(self) -> Dict[str, Any]:
        return {
            "graph_mb_data": self.__gnn_model.initialize_minibatch(),
            "target_classes": []
        }

    def extend_minibatch_with(
        self, tensorized_datapoint: TensorizedGraph2ClassSample, partial_minibatch: Dict[str, Any]
    ) -> bool:
        partial_minibatch["target_classes"].extend(tensorized_datapoint.supernode_target_classes)
        return self.__gnn_model.extend_minibatch_with(
            tensorized_datapoint.graph, partial_minibatch["graph_mb_data"]
        )

    def finalize_minibatch(
        self, accumulated_minibatch_data: Dict[str, Any], device: Any
    ) -> Dict[str, Any]:
        return {
            "graph_mb_data": self.__gnn_model.finalize_minibatch(
                accumulated_minibatch_data["graph_mb_data"], device
            ),
            "target_classes": torch.tensor(
                accumulated_minibatch_data["target_classes"], dtype=torch.int64, device=device
            )
        }
    

    def report_accuracy(
        self,
        dataset: [XGraph],
        trained_network: Graph2ClassModule,
        device: Union[str, torch.device],
    ) -> float:
        trained_network.eval()

        # trained_network._Graph2ClassModule__gnn._GraphNeuralNetwork__node_embedder._LinearFeatureEmbedder__linear_map.weight.data = torch.Tensor([[0.0,1.0]])
        # trained_network._Graph2ClassModule__gnn._GraphNeuralNetwork__message_passing_layers._modules['0']._MlpMessagePassingLayer__edge_message_transformation_layers[0]._MLP__mlp_modules[1].weight.data = torch.tensor([[1.0,0.0]])
        # trained_network._Graph2ClassModule__gnn._GraphNeuralNetwork__message_passing_layers._modules['0']._MlpMessagePassingLayer__edge_message_transformation_layers[1]._MLP__mlp_modules[1].weight.data = torch.tensor([[1.0,0.0]])
        # #trained_network._Graph2ClassModule__gnn._GraphNeuralNetwork__message_passing_layers._modules['0']._MlpMessagePassingLayer__edge_message_transformation_layers[2]._MLP__mlp_modules[1].weight.data = torch.tensor([[1.0,0.0]])
        # trained_network._Graph2ClassModule__gnn._GraphNeuralNetwork__message_passing_layers._modules['0']._MlpMessagePassingLayer__state_update[0].weight.data = torch.tensor([[1.0]])
        # trained_network._Graph2ClassModule__node_to_class.bias.data = torch.tensor([0.5,0.0])
        # trained_network._Graph2ClassModule__node_to_class.weight.data = torch.tensor([[0.0],[1.0]])


        num_correct, num_elements = 0, 0
        for mb_data, _ in self.minibatch_iterator(
            self.tensorize_dataset(dataset), device, max_minibatch_size=1
        ):
            predictions = trained_network.predict(mb_data["graph_mb_data"])
            #print(predictions)
            test = False
            for target, prediction in zip(mb_data["target_classes"], predictions):
                num_elements += 1
                #print(prediction)
                if torch.argmax(prediction) == target:
                    num_correct += 1
                else:
                    test = True
        return num_correct / num_elements