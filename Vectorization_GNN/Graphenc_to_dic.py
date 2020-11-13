from torch import sort
from torch.utils import data
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from tqdm import tqdm
import torch
import networkx as nx
with open("/Users/benediktschesch/MyEnv/Vectorization_GNN/temp/Vect_graphs_data.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()
data_points = raw_data["X"]
X = []
positive = 0
total = 0
histogram = {}
for data_point in tqdm(data_points):
    num_tasklets = 0
    for node in data_point["G"].nodes(data = True):
        if node[1]["attr"]["Type"][2] == 1:
            total += 1
            if node[1]["attr"]["Result"] == 1:
                num_tasklets += 1
                positive += 1
    if num_tasklets in histogram:
        histogram[num_tasklets] += 1
    else:
        histogram[num_tasklets] = 1
    result = {}
    result["target"] = data_point["target"]
    result["target_nodes"] = data_point["target_nodes"]
    dic = {}
    G = data_point["G"]
    dic["node_data"] = [n[1]["attr"] for n in G.nodes(data= True)]
    source = torch.Tensor([e[0] for e in G.edges(data= False)]).type(torch.LongTensor)
    dest =torch.Tensor([e[1] for e in G.edges(data= False)]).type(torch.LongTensor)
    dic["adjacency_lists"] = [(source,dest)]
    dic["node_to_graph_idx"] = [0 for i in range(len(G.nodes()))]
    dic["reference_node_graph_idx"] = {}
    dic["reference_node_ids"] = {}
    dic["num_graphs"] = 1
    result["G"] = dic
    X.append(result)

for i in sorted(histogram):
    print(i,histogram[i])
with open("/Users/benediktschesch/MyEnv/Vectorization_GNN/temp/Vect_dic_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump({"X":X,"dim_in":raw_data["dim_in"],"total":total,"positive":positive})
