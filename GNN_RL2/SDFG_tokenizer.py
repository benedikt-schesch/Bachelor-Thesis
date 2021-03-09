import os
import pickle
import sys
import copy
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import Encoder
import torch
import statistics


def one_hot(index,size):
    res = [0 for i in range(size)]
    res[index] = 1
    return res

def check_params(tilling):
    for i in tilling[1:]:
        if i != 1:
            return False
    return True


#Type one-hot encoding dictionary
type_dic = {}
type_dic["MapEntry"] =   torch.Tensor([1,0,0,0,0,0])
type_dic["MapExit"] =    torch.Tensor([0,1,0,0,0,0])
type_dic["Tasklet"] =    torch.Tensor([0,0,1,0,0,0])
type_dic["AccessNode"] = torch.Tensor([0,0,0,1,0,0])
type_dic["NestedSDFG"] = torch.Tensor([0,0,0,0,1,0])
type_dic["Memlet"] =     torch.Tensor([0,0,0,0,0,1])


path = "GNN_RL2/ENC_SDFGS"
paths = []
for root, dirs, files in os.walk(path):
    for file in files:
        paths.append(os.path.join(root, file))

size = [1,4,16,64,256,1024]
max_num_param = 0
max_num_map_entry = 0
max_free_symbols = 0
Params = []
Speedups = []
total = 0
positive = 0
for path in paths:
    data_point = pickle.load(open(path, "rb"))
    max_num_param = max(max_num_param,data_point["max_num_param"])
    max_num_map_entry = max(max_num_map_entry,data_point["num_map_entry"])
    max_free_symbols = max(max_free_symbols,data_point["num_free_symbols"])


encoder = Encoder(max_free_symbols,max_num_param,max_num_map_entry)
for id,path in enumerate(paths):
    data_point = pickle.load(open(path, "rb"))
    encoder.shuffle_sym()
    for augment in range(1):
        new_data = copy.deepcopy(data_point)
        #Encode the nodes
        for node in new_data["G"]["node_data"]:
            if node["Type"] == "MapEntry":
                node["data"] = torch.Tensor(encoder.encode(node["data"])).type(torch.LongTensor)
            if node["Type"] == "Memlet":
                node["data"] = torch.Tensor(encoder.encode(node["data"])).type(torch.LongTensor)
            node["Type"] = type_dic[node["Type"]]
        
        new_data["G"]["adjacency_lists"] = [torch.Tensor(arr).type(torch.LongTensor).view(2,-1) for arr in new_data["G"]["adjacency_lists"]]
        new_data["G"]["node_to_graph_idx"] = torch.zeros(len(new_data["G"]["node_data"])).type(torch.LongTensor)
        new_data["G"]["reference_node_graph_idx"] = {}
        new_data["G"]["reference_node_ids"] = {}
        

        baseline_times = statistics.median(new_data["timings"][0]["time"])
        
        best_timing = statistics.median(new_data["timings"][0]["time"])
        result = [size.index(1)]
        speedup_dic = {size.index(1):1.0}
        for times in new_data["timings"][1:]:
            if check_params(times["tilling"]):
                if statistics.median(times["time"])<best_timing:
                    best_timing = statistics.median(times["time"])
                    result = [size.index(times["tilling"][0])]
                if statistics.median(times["time"]) == 0:
                    best_timing = 0
                    break
                speedup_dic[size.index(times["tilling"][0])] = baseline_times*1.0/statistics.median(times["time"])
        if len(new_data["timings"][1]["tilling"]) > 1:
            continue
        if best_timing == 0:
            continue
        speedup = baseline_times*1.0/best_timing
        Speedups.append(speedup)
        new_data["speedup"] = speedup
        if speedup > 1.00:
            new_data["results"] = [1]
        else:
            new_data["results"] = [0]
        total += 1
        if new_data["results"][0] == 1:
            positive += 1
        new_data["speedup_dic"] = speedup_dic
        del new_data["timings"]
        new_data["map_entry"] = data_point["G"]["node_data"][data_point["map_entry_idx"]]
        with open("GNN_RL2/dataset/data_"+str(id)+".pkl", "wb") as fp:
            pickle.dump(new_data,fp)

raw_data = {}
raw_data["Average Speedup"] = statistics.mean(Speedups)
raw_data["dim_in"] = len(encoder)
raw_data["encoder"] = encoder
raw_data["max_num_param"] = max_num_param
with open("GNN_RL2/metadata.pkl", "wb") as fp:
    pickle.dump(raw_data,fp)
avg_speedup = statistics.mean(Speedups)
print("Average_Speedup ",avg_speedup)