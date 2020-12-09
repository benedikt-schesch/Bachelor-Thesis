#
# This file defines the GNN structure
#
import torch
from ptgnn.neuralmodels.gnn import GraphData
from ptgnn.neuralmodels.embeddings.linearmapembedding import FeatureRepresentationModel
from ptgnn.neuralmodels.gnn import GraphNeuralNetworkModel
from ptgnn.neuralmodels.gnn.messagepassing import GatedMessagePassingLayer, MlpMessagePassingLayer
from ptgnn.neuralmodels.gnn.messagepassing.residuallayers import ConcatResidualLayer
import torch
from torch import nn
from ptgnn.neuralmodels.gnn.graphneuralnetwork import GraphNeuralNetworkModel
import networkx as nx


def create_graph2class_gnn_model(hidden_state_size: int = 2, embedding_size = 2,dropout_rate: float = 0.1):
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
            r1.pass_through_dummy_layer(),
            mlp_mp_constructor(),
            mlp_mp_constructor(),
            mlp_mp_constructor(),
            r1,
            mlp_mp_after_res_constructor(),
            r2.pass_through_dummy_layer(),
            mlp_mp_constructor(),
            mlp_mp_constructor(),
            mlp_mp_constructor(),
            r2,
            mlp_mp_after_res_constructor(),
        ]

    return GraphNeuralNetworkModel(
            node_representation_model=FeatureRepresentationModel(embedding_size=embedding_size),
            message_passing_layer_creator=create_mlp_mp_layers,
            max_nodes_per_graph=100000,
            max_graph_edges=500000,
            introduce_backwards_edges=False,
            add_self_edges=False,
            stop_extending_minibatch_after_num_nodes=120000,
        )


class GNN(nn.Module):
    def __init__(self,dim_in,embedding_dim = 64,dim_hidden = 64,num_layers = 1,\
        transforms = []):
        super().__init__()
        self.dim_in = dim_in
        self.dim_hidden = dim_hidden
        self.embedding_dim = embedding_dim
        self.num_layers = num_layers
        self.word_embeddings = nn.Embedding(dim_in, embedding_dim)
        self.map = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        self.memlet = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        self.num_trans = len(transforms)
        self.trans_layers = []
        for elem in transforms:
            l = elem*(dim_hidden+6)
            operations = []
            operations.append(nn.Linear(l,l,bias = True))
            operations.append(nn.ReLU())
            operations.append(nn.Linear(l, out_features=2,bias = True))
            nn.init.xavier_uniform_(operations[0].weight)
            nn.init.xavier_uniform_(operations[2].weight)
            nn.init.zeros_(operations[0].bias)
            nn.init.zeros_(operations[2].bias)
            self.trans_layers.append(operations)
        self.gnn_model = create_graph2class_gnn_model(hidden_state_size=dim_hidden+6,embedding_size = dim_hidden+6)
    
    def compute_metada(self,data_points,device):
        data = []
        for data_point in data_points:
            G = data_point["G"]
            node_information = [self.node_representation(i)[0] for i in G["node_data"]]
            dic = {}
            for j in range(len(range(len(G["adjacency_lists"])))):
                edges = []
                for i in range(G["adjacency_lists"][j][0].shape[1]):
                    a = G["adjacency_lists"][j][0][0][i].item()
                    b = G["adjacency_lists"][j][0][1][i].item()
                    edges.append([a,b])
                dic["Type"+str(j)] = edges
            graph_data = GraphData(node_information,dic,{})
            data.append(graph_data)
        self.gnn_model.compute_metadata(data)
        self.gnn = self.gnn_model.build_neural_module()
        self.gnn.to(device)

    def node_representation(self,e):
        type_tensor = e["Type"]
        if e["Type"][0][0] == 1:
            data = e['data']
            data = self.word_embeddings(data).view(len(data[0]),-1 , self.embedding_dim)
            hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
            data, _ = self.map(data, hidden)
            return torch.cat((type_tensor[0], data[-1][0])).view(1,-1)
        elif e["Type"][0][5] == 1:
            data = e['data']
            data = self.word_embeddings(data).view(len(data[0]),-1 , self.embedding_dim)
            hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
            data, _ = self.memlet(data, hidden)
            return torch.cat((type_tensor[0], data[-1][0])).view(1,-1)
        else:
            return torch.cat((type_tensor[0], torch.zeros(self.dim_hidden))).view(1,-1)
    
    def compute_node_representations(self,X):
        res = torch.zeros((1,6+self.dim_hidden),requires_grad=True)
        for e in X:
            res = torch.cat((res,self.node_representation(e)))
        return res[1:]

    def forward(self,X,targets):
        X["node_data"] = {"features":self.compute_node_representations(X["node_data"])}
        X["node_to_graph_idx"] = X["node_to_graph_idx"][0]
        X["num_graphs"] = 1
        for i in range(len(X["adjacency_lists"])):
            X["adjacency_lists"][i] = X["adjacency_lists"][i][0]
        #["adjacency_lists"][0] = (X["adjacency_lists"][0][0][0],X["adjacency_lists"][0][1][0])
        result = self.gnn(**X).output_node_representations
        ret = []
        for i in range(self.num_trans):
            res_trans = torch.zeros(len(targets[i][0]), 2)
            for j,elem in enumerate(targets[i][0]):
                x = self.trans_layers[i][0](result[elem].view(-1))
                x = self.trans_layers[i][1](x)
                x = self.trans_layers[i][2](x)
                res_trans[j,:] = x
            ret.append(res_trans)
        return ret