from typing import Any, Counter, Dict, Iterator, List, NamedTuple, Optional, Tuple, Union
from typing_extensions import TypedDict

import numpy as np
import torch
from dpu_utils.mlutils import Vocabulary
from torch import Tensor, nn

from ptgnn.baseneuralmodel import AbstractNeuralModel, ModuleWithMetrics
from ptgnn.baseneuralmodel.utils.data import enforce_not_None
from ptgnn.neuralmodels.gnn import GnnOutput, GraphData, TensorizedGraphData
from ptgnn.neuralmodels.gnn.graphneuralnetwork import GraphNeuralNetwork, GraphNeuralNetworkModel
import networkx as nx

XGraph = TypedDict(
    "XGraph",
    {
        "nodes": List,
        "edges": dict,
        "result": int,
    },
)

Prediction = Tuple[XGraph, Dict[int,int]]


class TensorizedGraph2ClassSample(NamedTuple):
    graph: XGraph

class Graph2ClassModule(nn.Module):
    def __init__(self, gnn: GraphNeuralNetwork,num_target_classes):
        super().__init__()
        self.__gnn = gnn
        self.__node_to_class = nn.Linear(
            in_features=gnn.output_node_state_dim, out_features=2,bias = True
        )
        nn.init.uniform_(self.__node_to_class.weight)
        nn.init.zeros_(self.__node_to_class.bias)
        self.__loss = nn.CrossEntropyLoss()

 
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

    def __convert(self, x_graph: XGraph) -> Tuple[GraphData[int], List[int]]:
        edge_dic = x_graph["edges"]#{"edges_type1":[]}
        edge_dic
        info = x_graph["nodes"]
        return (
            GraphData[str](
                node_information=info,
                edges=edge_dic,
                reference_nodes = {}
            )
        )

    def build_neural_module(self) -> Graph2ClassModule:
        return Graph2ClassModule(gnn=self.__gnn_model.build_neural_module(), num_target_classes=2)

    def update_metadata_from(self, datapoint: XGraph) -> None:
        graph_data = self.__convert(datapoint)
        self.__gnn_model.update_metadata_from(graph_data)

    # region Minibatching
    def initialize_minibatch(self) -> Dict[str, Any]:
        return {
            "graph_mb_data": self.__gnn_model.initialize_minibatch()
        }

    def extend_minibatch_with(
        self, tensorized_datapoint: TensorizedGraph2ClassSample, partial_minibatch: Dict[str, Any]
    ) -> bool:
        return self.__gnn_model.extend_minibatch_with(
            tensorized_datapoint.graph, partial_minibatch["graph_mb_data"]
        )

    def finalize_minibatch(
        self, accumulated_minibatch_data: Dict[str, Any], device: Any
    ) -> Dict[str, Any]:
        return {
            "graph_mb_data": self.__gnn_model.finalize_minibatch(
                accumulated_minibatch_data["graph_mb_data"], device
            )
        }