from aenum import convert
import dace
import dace.subsets
from dace.transformation.dataflow import vectorization
import numpy as np
import os, glob
import tensorflow as tf
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

with open("/Users/benediktschesch/MyEnv/temp/Vect_graphs_normalized.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()
max_num_map_entry = raw_data["max_num_map_entry"]
max_num_param = raw_data["max_num_param"]
data_points = raw_data["data"]
max_free_symbols = raw_data["max_free_symbols"]
encoder = Encoder(max_free_symbols,max_num_param,max_num_map_entry)
X = []
positive = 0
total = 0
for data_point in tqdm(data_points):
    G = data_point["G"]
    target_nodes = []
    targets = []
    type_dic = {}
    type_dic["MapEntry"] =   torch.Tensor([1,0,0,0,0,0])
    type_dic["MapExit"] =    torch.Tensor([0,1,0,0,0,0])
    type_dic["Tasklet"] =    torch.Tensor([0,0,1,0,0,0])
    type_dic["AccessNode"] = torch.Tensor([0,0,0,1,0,0])
    type_dic["NestedSDFG"] = torch.Tensor([0,0,0,0,1,0])
    type_dic["Memlet"] =     torch.Tensor([0,0,0,0,0,1])
    highest_node_number = 0
    for node in G.nodes(data = True):
        if node[1]["attr"]["Type"] == "Tasklet":
            target_nodes.append(node[0])
            targets.append(node[1]["attr"]["Result"])
            if node[1]["attr"]["Result"] == 1:
                positive += 1
            total += 1
        if node[1]["attr"]["Type"] == "MapEntry":
            node[1]["attr"]["data"] = torch.Tensor(encoder.encode(map2str(node[1]["attr"]["data"]))).type(torch.LongTensor)
        node[1]["attr"]["Type"] = type_dic[node[1]["attr"]["Type"]]
        highest_node_number = max(node[0],highest_node_number)
    edges_to_add = []
    node_to_add = []
    for edge in G.edges(data = True):
        highest_node_number += 1
        data = edge[2]
        dic = {"attr":{"data":torch.Tensor(encoder.encode(mem2str(data['attr']))).type(torch.LongTensor),"Type":type_dic["Memlet"]}}
        node_to_add += [(highest_node_number,dic)]
        edges_to_add += [(edge[0],highest_node_number),(highest_node_number,edge[1])]
        del edge[2]["attr"]
    G.add_nodes_from(node_to_add)
    G.add_edges_from(edges_to_add)
    targets = torch.Tensor(targets).type(torch.LongTensor)
    if len(target_nodes) != 0:
        X.append({"G":G,"target_nodes":target_nodes,"target":targets})

with open("/Users/benediktschesch/MyEnv/temp/Vect_graphs_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump({"X":X,"dim_in":len(encoder)})
