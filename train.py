import random
from pathlib import Path
from typing_extensions import TypedDict
import torch
from docopt import docopt
from dpu_utils.utils import RichPath, run_and_debug

import networkx as nx
from ptgnn.baseneuralmodel.trainer import AbstractScheduler

from ptgnn.baseneuralmodel import ModelTrainer
from ptgnn.baseneuralmodel.utils.amlutils import configure_logging, log_run
from ptgnn.baseneuralmodel.utils.data import LazyDataIterable
from LoopDetection import Graph2Class
from ptgnn.neuralmodels.embeddings.linearmapembedding import (
    FeatureRepresentationModel,
)
from ptgnn.neuralmodels.gnn import GraphNeuralNetworkModel
from ptgnn.neuralmodels.gnn.messagepassing import GatedMessagePassingLayer, MlpMessagePassingLayer
from ptgnn.neuralmodels.gnn.messagepassing.residuallayers import ConcatResidualLayer

def create_graph2class_gnn_model(hidden_state_size: int = 2, dropout_rate: float = 0.1):
    def create_ggnn_mp_layers(num_edges: int):
        ggnn_mp = GatedMessagePassingLayer(
            state_dimension=hidden_state_size,
            message_dimension=hidden_state_size,
            num_edge_types=num_edges,
            message_aggregation_function="max",
            dropout_rate=dropout_rate,
        )
        r1 = ConcatResidualLayer(hidden_state_size)
        return [
            r1.pass_through_dummy_layer(),
            ggnn_mp,
            ggnn_mp,
            ggnn_mp,
            ggnn_mp,
            ggnn_mp,
            ggnn_mp,
            ggnn_mp,
            r1,
            GatedMessagePassingLayer(
                state_dimension=2 * hidden_state_size,
                message_dimension=hidden_state_size,
                num_edge_types=num_edges,
                message_aggregation_function="max",
                dropout_rate=dropout_rate,
            ),
        ]

    def create_mlp_mp_layers(num_edges: int):
        mlp_mp_constructor = lambda: MlpMessagePassingLayer(
            input_state_dimension=hidden_state_size,
            message_dimension=hidden_state_size,
            output_state_dimension=hidden_state_size,
            num_edge_types=num_edges,
            message_aggregation_function="max",
            use_layer_norm = False,
            message_activation = None,
            dropout_rate=0,
            dense_activation = None,
        )
        mlp_mp_after_res_constructor = lambda: MlpMessagePassingLayer(
            input_state_dimension=2 * hidden_state_size,
            message_dimension=2 * hidden_state_size,
            output_state_dimension=hidden_state_size,
            num_edge_types=num_edges,
            message_aggregation_function="max",
            use_layer_norm = False,
            message_activation = None,
            dropout_rate=0,
        )
        r1 = ConcatResidualLayer(hidden_state_size)
        r2 = ConcatResidualLayer(hidden_state_size)
        return [
            # r1.pass_through_dummy_layer(),
            mlp_mp_constructor(),
            #mlp_mp_constructor(),
            #mlp_mp_constructor(),
            # r1,
            # mlp_mp_after_res_constructor(),
            # r2.pass_through_dummy_layer(),
            # mlp_mp_constructor(),
            # mlp_mp_constructor(),
            # mlp_mp_constructor(),
            # r2,
            # mlp_mp_after_res_constructor(),
        ]

    return Graph2Class(
        gnn_model=GraphNeuralNetworkModel(
            node_representation_model=FeatureRepresentationModel(embedding_size=2),
            message_passing_layer_creator=create_mlp_mp_layers,
            max_nodes_per_graph=100000,
            max_graph_edges=500000,
            introduce_backwards_edges=False,
            add_self_edges=True,
            stop_extending_minibatch_after_num_nodes=120000,
        ),
    )
def load_from_folder(path: RichPath, shuffle: bool):
    all_files = path.get_filtered_files_in_dir("*.jsonl.gz")
    if shuffle:
        random.shuffle(all_files)
    for file in all_files:
        yield from file.read_as_jsonl()

def generate_random_graph(num_graphs,max_num_nodes):
    class GraphRandomizer(object):
        def __init__(self, num_graphs):
            self.num_graphs = num_graphs
            self.counter = 0
        
        def __iter__(self):
           return self

        def __next__(self):
            if self.counter >= self.num_graphs:
                self.counter = 0
                raise StopIteration
            self.counter += 1
            n = random.randint(2, max_num_nodes)
            G = nx.gnm_random_graph(n,random.randint(0,n))
            res = [0 for i in range(len(G.nodes))]
            for i in nx.descendants(G,0):
                res[i] = 1
            res[0] = 1
            graph:  XGraph = {"nodes": G.nodes,"edges": G.edges,"result": res}
            return graph

    '''
    list = []
    for i in range(num_graphs):
        n = random.randint(2, max_num_nodes)
        G = nx.gnm_random_graph(n,random.randint(0,n))
        res = [0 for i in range(len(G.nodes))]
        for i in nx.descendants(G,0):
            res[i] = 1
        res[0] = 1
        graph:  XGraph = {"nodes": G.nodes,"edges": G.edges,"result": res}
        list.append(graph)
    return list
    '''
    return GraphRandomizer(num_graphs)

def run(training_data,validation_data):
    #training_data_path = RichPath.create(arguments["TRAIN_DATA_PATH"], azure_info_path)
    #training_data = LazyDataIterable(lambda: load_from_folder(training_data_path, shuffle=True))
    #validation_data_path = RichPath.create(arguments["VALID_DATA_PATH"], azure_info_path)
    #validation_data = LazyDataIterable(
        #lambda: load_from_folder(validation_data_path, shuffle=False)
    #)

    model_path = Path("model.pkl.gz")
    assert model_path.name.endswith(".pkl.gz"), "MODEL_FILENAME must have a `.pkl.gz` suffix."

    initialize_metadata = True
    restore_path = False
    if restore_path:
        initialize_metadata = False
        model, nn = Graph2Class.restore_model(Path(restore_path))
    else:
        nn = None
        model = create_graph2class_gnn_model()

    def create_optimizer(parameters):
        return torch.optim.SGD(parameters,lr=0.5)

    class sched(AbstractScheduler):
        def __init__(self,optim):
            self.optim = optim

        def step(self, epoch_idx: int, epoch_step: int) -> None:
            if epoch_idx > 6:
                self.optim.param_groups[0]['lr'] = 0.01
            if epoch_idx > 12:
                self.optim.param_groups[0]['lr'] = 0.001
            if epoch_idx > 18:
                self.optim.param_groups[0]['lr'] = 0.0001
            if epoch_step == 63:
                print(self.optim.param_groups[0]['lr'])
    def scheduler_creator(optim):
        return sched(optim)

    trainer = ModelTrainer(
        model,
        model_path,
        max_num_epochs=64,
        minibatch_size=1,
        optimizer_creator=create_optimizer,
        scheduler_creator=scheduler_creator,
        clip_gradient_norm=1,
        target_validation_metric="Accuracy",
        target_validation_metric_higher_is_better=True,
    )
    if nn is not None:
        trainer.neural_module = nn

    trainer.register_train_epoch_end_hook(
        lambda model, nn, epoch, metrics: None
    )
    trainer.register_validation_epoch_end_hook(
        lambda model, nn, epoch, metrics: None
    )

    trainer.train(
        training_data,
        validation_data,
        show_progress_bar=True,
        initialize_metadata=initialize_metadata,
        parallelize=True,
        patience=4,
        store_tensorized_data_in_memory=True,
    )
    list = []
    G = nx.Graph()
    G.add_nodes_from([0,1,2])
    G.add_edges_from([(1,2),(0,2)])
    res = [0 for i in range(len(G.nodes))]
    for i in nx.descendants(G,0):
        res[i] = 1
    res[0] = 1
    graph:  XGraph = {"nodes": G.nodes,"edges": G.edges,"result": res}
    list.append(graph)
    sizes = [4,16, 20, 50,1024]
    test_data = []
    for i in sizes:
        test_data.append(generate_random_graph(512,i))

    for size, graphs in zip(sizes,test_data):
        acc2 = model.report_accuracy(
            training_data,
            trainer.neural_module,
            device=torch.device("cuda:0" if torch.cuda.is_available() else "cpu"),
        )
        print(f"Training accuracy:{size}  {acc2:%}")

import networkx as nx
XGraph = TypedDict(
    "XGraph",
    {
        "nodes": nx.classes.reportviews.NodeView,
        "edges": nx.classes.reportviews.EdgeView,
        "result": list,
    },
)

if __name__ == "__main__":
    
    training_data = generate_random_graph(2048,16)
    
    validation_data = generate_random_graph(1024,16)

    run(training_data,validation_data)