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
from tqdm import tqdm
import os
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import memlet2dic,map2dic

with open("/Users/benediktschesch/MyEnv/temp/Vect_graphs_raw.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()

max_params = raw_data["max_params"]
max_free_symbols = raw_data["max_free_symbols"]
data_points = raw_data["data"]
max_num_map_entry = 0
max_num_param = 0
for data in tqdm(data_points):
    G = data["G"]
    params = data["params"]
    free_symbols = data["free_symbols"]
    str_params_dic = {}
    freesymbol_dic = {}
    for count,sym in enumerate(list(free_symbols)):
        freesymbol_dic[dace.symbol(sym)] = "N"+str(count)
    num_map_entry = 0
    for node in G.nodes(data = True):
        if node[1]["attr"]["Type"] == "MapEntry":
            for i in range(node[1]["attr"]["data"]["num_params"]):
                str_params_dic[node[1]["attr"]["data"]["param"+str(i)]] = "i"+str(num_map_entry)+str(i)
                freesymbol_dic[dace.symbol(node[1]["attr"]["data"]["param"+str(i)])] = "i"+str(num_map_entry)+str(i)
            max_num_param = max(max_num_param,node[1]["attr"]["data"]["num_params"])
            num_map_entry += 1
    max_num_map_entry = max(max_num_map_entry,num_map_entry)
    
    for node in G.nodes(data = True):
        if node[1]["attr"]["Type"] == "MapEntry":
            node[1]["attr"]["data"] = map2dic(node[1]["attr"]["data"],freesymbol_dic,str_params_dic)
    for edge in G.edges(data = True):
        edge[2]['attr'] = memlet2dic(edge[2]['attr'],freesymbol_dic)
    del data["params"]
    del data["free_symbols"]


output = {"max_free_symbols":max_free_symbols,"max_params":max_params,"data":data_points,"max_num_map_entry":max_num_map_entry,"max_num_param":max_num_param}
with open("/Users/benediktschesch/MyEnv/temp/Vect_graphs_normalized.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(output)