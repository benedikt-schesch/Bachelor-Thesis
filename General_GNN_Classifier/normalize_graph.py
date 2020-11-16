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

#Import Graphs
with open("/Users/benediktschesch/MyEnv/temp/Graphs_raw.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()

#Intialize parameters
max_num_map_entry = 0
max_num_param = 0


for data in tqdm(raw_data["data"]):

    #Initialization
    G = data["G"]
    params = data["params"]
    free_symbols = data["free_symbols"]
    str_params_dic = {}
    freesymbol_dic = {}
    num_map_entry = 0

    #Create free symbol dictionary
    for count,sym in enumerate(list(free_symbols)):
        freesymbol_dic[dace.symbol(sym)] = "N"+str(count)
    
    #Create Parameter dictionary
    for node in G.nodes(data = True):
        if node[1]["Type"] == "MapEntry":
            for i in range(node[1]["attr"]["num_params"]):
                str_params_dic[node[1]["attr"]["param"+str(i)]] = "i"+str(num_map_entry)+str(i)
                freesymbol_dic[dace.symbol(node[1]["attr"]["param"+str(i)])] = "i"+str(num_map_entry)+str(i)
            max_num_param = max(max_num_param,node[1]["attr"]["num_params"])
            num_map_entry += 1
    max_num_map_entry = max(max_num_map_entry,num_map_entry)
    
    #Normalize node data
    for node in G.nodes(data = True):
        if node[1]["Type"] == "MapEntry":
            node[1]["attr"] = map2dic(node[1]["attr"],freesymbol_dic,str_params_dic)
    
    #Normalize node data
    for edge in G.edges(data = True):
        edge[2]['attr'] = memlet2dic(edge[2]['attr'],freesymbol_dic)

    #Remove no longer relevant parameters
    del data["params"]
    del data["free_symbols"]

#Store data
raw_data["max_num_map_entry"] = max_num_map_entry
raw_data["max_num_param"] = max_num_param
with open("/Users/benediktschesch/MyEnv/temp/Graphs_normalized.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(raw_data)