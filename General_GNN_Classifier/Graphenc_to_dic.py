#
#We take the final encoding our graph and tensorize it such that ptgnn can read it
#
from dace import symbolic
from tqdm import tqdm
import torch
import networkx as nx
with open("/Users/benediktschesch/MyEnv/temp/Graphs_embeded.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()

#data_points = raw_data["data"]

tasklets = 0
map_entries = 0
transformations_data_task = [[i.__name__,0,0] for i in raw_data["transformations_tasklet"]]
transformations_data_map = [[i.__name__,0,0] for i in raw_data["transformations_map_entry"]]

#Convert data points to tensors
def compute(data_points):
    for data_point in tqdm(data_points):
        num_tasklets = 0
        dic = {}
        G = data_point["G"]
    

        for dic2 in data_point["list_trans_map_entry"]:
            dic2["results"] = torch.Tensor(dic2["results"]).type(torch.LongTensor)
        for dic2 in data_point["list_trans_tasklet"]:
            dic2["results"] = torch.Tensor(dic2["results"]).type(torch.LongTensor)
        dic["node_data"] = [n[1] for n in G.nodes(data= True)]
        source = torch.Tensor([e[0] for e in G.edges(data= False)]).type(torch.LongTensor)
        dest =torch.Tensor([e[1] for e in G.edges(data= False)]).type(torch.LongTensor)
        dic["adjacency_lists"] = [(source,dest)]
        dic["node_to_graph_idx"] = torch.zeros(len(G.nodes)).type(torch.LongTensor)
        dic["reference_node_graph_idx"] = {}
        dic["reference_node_ids"] = {}
        
        data_point["tasklet"] = torch.Tensor(data_point["tasklet"]).type(torch.LongTensor)
        data_point["map_entry"] = torch.Tensor(data_point["map_entry"]).type(torch.LongTensor)
        del data_point["file"]
        data_point["G"] = dic

compute(raw_data["X_train"])
compute(raw_data["X_test"])
raw_data["transformations_data_map"] = transformations_data_map
raw_data["transformations_data_task"] = transformations_data_task
with open("/Users/benediktschesch/MyEnv/temp/Graph_train_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(raw_data)
