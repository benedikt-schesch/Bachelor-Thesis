#
#We take the normal form of the graph and encode and tokenize it
#Data augmentation techniques have been added
#

from aenum import convert
import dace
import dace.subsets
from dace.transformation.dataflow import vectorization
import numpy as np
import os, glob
import tensorflow as tf
import copy
from tensorflow import keras
from sklearn.model_selection import train_test_split
import random
from dace.sdfg import nodes, SDFG, propagation
import re
import torch.nn as nn
import torch
from torch.utils.data import TensorDataset, DataLoader, Dataset
from torch import empty, optim
import pickle
from dace.sdfg.graph import SubgraphView
from dace.sdfg.nodes import MapEntry, Tasklet
from dace.transformation.optimizer import Optimizer
from dace.transformation.dataflow import Vectorization
from dace.sdfg.state import SDFGState
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from dace.sdfg import has_dynamic_map_inputs
import networkx as nx
from tqdm import tqdm
import os
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import Encoder,map2str,mem2str

#Type one-hot encoding dictionary
type_dic = {}
type_dic["MapEntry"] =   torch.Tensor([1,0,0,0,0,0])
type_dic["MapExit"] =    torch.Tensor([0,1,0,0,0,0])
type_dic["Tasklet"] =    torch.Tensor([0,0,1,0,0,0])
type_dic["AccessNode"] = torch.Tensor([0,0,0,1,0,0])
type_dic["NestedSDFG"] = torch.Tensor([0,0,0,0,1,0])
type_dic["Memlet"] =     torch.Tensor([0,0,0,0,0,1])

#Open Data
with open("/Users/benediktschesch/MyEnv/temp/Normalized_data.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()

#Initialize Data
max_num_map_entry = raw_data["max_num_map_entry"]
max_num_param = raw_data["max_num_param"]
data_points = raw_data["data"]
max_free_symbols = raw_data["max_free_symbols"]
encoder = Encoder(max_free_symbols,max_num_param,max_num_map_entry)
data_train, data_test = train_test_split(data_points, test_size=0.2)

tasklets = 0
map_entries = 0
transformations_data_task = [[i.__name__,0,0] for i in raw_data["transformations_tasklet"]]
transformations_data_map = [[i.__name__,0,0] for i in raw_data["transformations_map_entry"]]

def gen_data(data_points):
    X = []
    for data_point in tqdm(data_points):
        encoder.shuffle_sym()
        for i in range(16):
            new_data = copy.deepcopy(data_point)
            #Encode the nodes
            for node in new_data["G"]["node_data"]:
                if node["Type"] == "MapEntry":
                    node["data"] = torch.Tensor(encoder.encode(node["data"])).type(torch.LongTensor)
                if node["Type"] == "Memlet":
                    node["data"] = torch.Tensor(encoder.encode(node["data"])).type(torch.LongTensor)
                node["Type"] = type_dic[node["Type"]]
            
            num_correct = sum(new_data["list_trans_map_entry"][0]["results"])
            total = len(new_data["tasklet"])
            source = torch.Tensor([e[0] for e in new_data["G"]["adjacency_lists"]]).type(torch.LongTensor)
            dest =torch.Tensor([e[1] for e in new_data["G"]["adjacency_lists"]]).type(torch.LongTensor)
            new_data["G"]["adjacency_lists"] = [(source,dest)]
            new_data["G"]["node_to_graph_idx"] = torch.zeros(len(new_data["G"]["node_data"])).type(torch.LongTensor)
            new_data["G"]["reference_node_graph_idx"] = {}
            new_data["G"]["reference_node_ids"] = {}
            new_data["tasklet"] = torch.Tensor(new_data["tasklet"]).type(torch.LongTensor)
            new_data["map_entry"] = torch.Tensor(new_data["map_entry"]).type(torch.LongTensor)
            for dic2 in new_data["list_trans_map_entry"]:
                dic2["results"] = torch.Tensor(dic2["results"]).type(torch.LongTensor)
            for dic2 in new_data["list_trans_tasklet"]:
                dic2["results"] = torch.Tensor(dic2["results"]).type(torch.LongTensor)
            del new_data["file"]
            X.append(new_data)

            #Compute statisctics about tasklet transformations
            for i in range(len(transformations_data_task)):
                transformations_data_task[i][2] += len(data_point["tasklet"])
                transformations_data_task[i][1] += sum(data_point["list_trans_tasklet"][i]["results"])
            #Compute statisctics about map_entry transformations
            for i in range(len(transformations_data_map)):
                transformations_data_map[i][2] += len(data_point["map_entry"])
                transformations_data_map[i][1] += sum(data_point["list_trans_map_entry"][i]["results"])
            if total == 0 or num_correct*1.0/total < 0.3:
                break
    return X


raw_data["X_test"] = gen_data(data_train)
raw_data["X_train"] = gen_data(data_test)
del raw_data["data"]
raw_data["transformations_data_map"] = transformations_data_map
raw_data["transformations_data_task"] = transformations_data_task
raw_data["dim_in"] = len(encoder)
with open("/Users/benediktschesch/MyEnv/temp/train_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(raw_data)