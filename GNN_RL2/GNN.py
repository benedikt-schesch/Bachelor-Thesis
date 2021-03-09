#
# This file defines the GNN structure
#
from numpy.core.fromnumeric import size
import torch
import ptgnn
from ptgnn.neuralmodels.gnn import GraphData
from ptgnn.neuralmodels.embeddings.linearmapembedding import FeatureRepresentationModel
from ptgnn.neuralmodels.gnn import GraphNeuralNetworkModel
from ptgnn.neuralmodels.gnn.messagepassing import GatedMessagePassingLayer, MlpMessagePassingLayer
from ptgnn.neuralmodels.gnn.messagepassing.residuallayers import ConcatResidualLayer
import torch
from torch import nn
from ptgnn.neuralmodels.gnn.graphneuralnetwork import GraphNeuralNetworkModel

def param_enc(index,size):
    res = torch.zeros(size)
    for i in range(index):
        res[i] = 1
    return res

def create_graph2class_gnn_model(hidden_state_size: int = 2, embedding_size = 2,dropout_rate: float = 0.1):
    def create_ggnn_mp_layers(num_edges: int):
        ggnn_mp = GatedMessagePassingLayer(
            state_dimension=hidden_state_size,
            message_dimension=hidden_state_size,
            num_edge_types=num_edges,
            message_aggregation_function="mean",
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
                message_aggregation_function="mean",
                dropout_rate=dropout_rate,
            ),
        ]

    def create_mlp_mp_layers(num_edges: int):
        mlp_mp_constructor = lambda: MlpMessagePassingLayer(
            input_state_dimension=hidden_state_size,
            message_dimension=hidden_state_size,
            output_state_dimension=hidden_state_size,
            num_edge_types=num_edges,
            message_aggregation_function="mean",
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
            message_aggregation_function="mean",
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
class OneHot(nn.Module):
  def __init__(self,vocab_size,embedding_dim):
    super().__init__()
    self.vocab_size = vocab_size
    assert vocab_size == embedding_dim
  def forward(self,x):
    result = torch.zeros((x.nelement(),self.vocab_size))
    for index,i in enumerate(x[0]):
        result[index][i] = 1
    return result

class Embedder(nn.Module):
    def __init__(self,vocab_size,size,max_num_param,embedding_dim = 64,dim_hidden = 64\
    ,num_layers = 1):
        super().__init__()
        self.max_num_param = max_num_param
        self.vocab_size = vocab_size
        self.dim_hidden = dim_hidden
        self.embedding_dim = embedding_dim
        self.num_layers = num_layers
        self.word_embeddings = nn.Embedding(vocab_size, embedding_dim)
        self.map = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        self.map_decode = nn.GRU(dim_hidden, dim_hidden,num_layers=num_layers)
        self.map_output_layer = nn.Linear(self.dim_hidden, vocab_size)
        self.memlet = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        self.memlet_decode = nn.GRU(dim_hidden, dim_hidden,num_layers=num_layers)
        self.memlet_output_layer = nn.Linear(self.dim_hidden, vocab_size)
    
    def map_embedding(self,x):
      data = x['data']
      data = self.word_embeddings(data).view(len(data[0]),-1 , self.embedding_dim)
      hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
      data, _ = self.map(data, hidden)
      return data[-1]

    def mem_embedding(self,x):
      data = x['data']
      data = self.word_embeddings(data).view(len(data[0]),-1 , self.embedding_dim)
      hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
      data, _ = self.memlet(data, hidden)
      return data[-1]

    def forward(self,x):
        if x["Type"][0][0] == 1:
            result = []
            data = self.map_embedding(x)
            input = torch.zeros((self.num_layers,1,self.dim_hidden))
            for i in range(len(x['data'][0])):
                input,data = self.map_decode(input,data.reshape(1,1,-1))
                result.append(input.reshape(-1))
            result = torch.stack(result)
            return self.map_output_layer(result)
        elif x["Type"][0][5] == 1:
            result = []
            data = self.mem_embedding(x)
            input = torch.zeros((self.num_layers,1,self.dim_hidden))
            for i in range(len(x['data'][0])):
                input,data = self.memlet_decode(input,data.reshape(1,1,-1))
                result.append(input.reshape(-1))
            result = torch.stack(result)
            return self.memlet_output_layer(result)
class GNN(nn.Module):
    def __init__(self,vocab_size,size,max_num_param,embedding_dim = 64,dim_hidden = 64\
        ,num_layers = 1):
        super().__init__()
        self.max_num_param = max_num_param
        self.vocab_size = vocab_size
        self.dim_hidden = dim_hidden
        self.embedding_dim = embedding_dim
        self.num_layers = num_layers
        self.word_embeddings = nn.Embedding(vocab_size, embedding_dim)
        self.map = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        self.memlet = nn.GRU(self.embedding_dim, dim_hidden,num_layers=num_layers)
        l = (dim_hidden+6)
        self.out1 = nn.Linear(l,l,bias = True)
        self.rel1 = nn.ReLU()
        self.out2 = nn.Linear(l,l,bias = True)
        self.rel2 = nn.ReLU()
        self.out3 = nn.Linear(l, out_features=2,bias = True)
        self.gnn_model = create_graph2class_gnn_model(hidden_state_size=dim_hidden+6,embedding_size = dim_hidden+6)
    
    def compute_metada(self,data_points,device):
        data = []
        for data_point in data_points:
            #GPU Support
            for i in range(len(data_point["G"]["adjacency_lists"])):
                data_point["G"]["adjacency_lists"][i] = data_point["G"]["adjacency_lists"][i].to(device)
            for i in data_point["G"]["node_data"]:
                if "data" in i:
                    i["data"] = i["data"].to(device)
            i["Type"]  = i["Type"].to(device)
            data_point["G"]["node_to_graph_idx"] = data_point["G"]["node_to_graph_idx"].to(device)
            #GPU Support
            
            G = data_point["G"]
            node_information = [self.node_representation(i)[0] for i in G["node_data"]]
            dic = {}
            for j in range(len(range(len(G["adjacency_lists"])))):
                edges = []
                for i in range(G["adjacency_lists"][j].shape[1]):
                    a = G["adjacency_lists"][j][0][i].item()
                    b = G["adjacency_lists"][j][1][i].item()
                    edges.append([a,b])
                dic["Type"+str(j)] = edges
            graph_data = GraphData(node_information,dic,{})
            data.append(graph_data)
        self.gnn_model.compute_metadata(data)
        self.gnn = self.gnn_model.build_neural_module()
        self.gnn.to(device)


    def todevice(self,device):
      self.gnn.to(device)
      self.word_embeddings.to(device)
      self.map.to(device)
      self.memlet.to(device)

    def node_representation(self,e):
        type_tensor = e["Type"]
        if e["Type"][0].item() == 1:
            data = e['data']
            data = self.word_embeddings(data).view(len(data),-1 , self.embedding_dim)
            hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
            data, _ = self.map(data, hidden)
            return torch.cat((type_tensor, data[-1][0])).view(1,-1)
        elif e["Type"][5].item() == 1:
            data = e['data']
            data = self.word_embeddings(data).view(len(data),-1 , self.embedding_dim)
            hidden = torch.zeros((self.num_layers,1,self.dim_hidden))
            data, _ = self.memlet(data, hidden)
            return torch.cat((type_tensor, data[-1][0])).view(1,-1)
        else:
            return torch.cat((type_tensor, torch.zeros(self.dim_hidden))).view(1,-1)
    
    def compute_node_representations(self,X):
        res = torch.zeros((1,6+self.dim_hidden),requires_grad=True)
        for e in X:
            res = torch.cat((res,self.node_representation(e)))
        return res[1:]

    def forward(self,X,map_entry_idx):
        X["node_data"] = {"features":self.compute_node_representations(X["node_data"])}
        X["num_graphs"] = 1
        X["edge_feature_data"] = []
        #for i in range(len(X["adjacency_lists"])):
        #    X["adjacency_lists"][i] = X["adjacency_lists"][i][0]
        #["adjacency_lists"][0] = (X["adjacency_lists"][0][0][0],X["adjacency_lists"][0][1][0])
        result = self.gnn(**X).output_node_representations
        x = result[map_entry_idx]
        x = self.out1(x)
        x = self.rel1(x)
        x = self.out2(x)
        x = self.rel2(x)
        x = self.out3(x)
        return x