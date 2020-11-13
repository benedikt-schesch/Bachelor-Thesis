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
from LSTM import LSTM_Encoder, Network
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
from dace.sdfg import has_dynamic_map_inputs
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from tqdm import tqdm
import json

def extract_map(map):
    dic = {}
    i = 0
    dict_free_symbol = {}
    for i in range(len(map.params)):
        dic["param"+str(i)] = map.params[i]
        dic["range"+str(i)] = [map.range[i][0],map.range[i][1],map.range[i][2]]
    return dic
    
def extract_memlet(Memlet):
    dictionary = {}
    dictionary["Volume"] = Memlet.data.volume
    dictionary["Dynamic"] = Memlet.data.dynamic
    num_range = 0
    if Memlet.data.is_empty():
        dictionary["empty"] = True
    else:
        dictionary["empty"] = False
        if isinstance(Memlet.data.subset, dace.subsets.Indices):
            rng = dace.subsets.Range.from_indices(Memlet.data.subset)
        else:
            rng = Memlet.data.subset
        for rge in rng.ranges:
            dictionary["Range"+str(num_range)] = rge
            num_range+=1
    return dictionary

def compute_paths():
    paths = []
    for root, dirs, files in tqdm(os.walk("/Users/benediktschesch/MyEnv")):
        for file in files:
            if file.endswith(".sdfg"):
                paths.append(os.path.join(root, file))
    with open("/Users/benediktschesch/MyEnv/Vectorization_paths.pkl", "wb") as fp:
        pickle.dump(paths, fp)
paths = []
compute_paths()
with open("/Users/benediktschesch/MyEnv/Vectorization_paths.pkl", "rb") as fp:   # Unpickling
    paths = pickle.load(fp)
#paths = paths[0:20]
count = 0
data_points = []
max_free_symbols = 0
max_params = 0
for file in tqdm(paths):
    try:
        sdfg = dace.SDFG.from_file(file)
    except:
        print("Not Valid SDFG at: "+str(file))
        continue
    opt = Optimizer(sdfg)
    vectorization_map_entry = [i.query_node(sdfg.sdfg_list[i.sdfg_id],i._map_entry) for i in opt.get_pattern_matches(patterns=[Vectorization])]
    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, MapEntry):
            dic_training = {}
            if has_dynamic_map_inputs(state,node):
                continue
            tasklet = state.out_edges(node)[0].dst
            if not isinstance(tasklet,Tasklet):
                continue
            free_symbols = set()
            #Get the Free symbols
            for Memlet in state.in_edges(tasklet)+state.out_edges(tasklet):
                for free_symbol in Memlet.data.free_symbols:
                     free_symbols.add(free_symbol)
            for free_symbol in node.free_symbols:
                free_symbols.add(free_symbol)
            dic_training["Free_symbols"] = free_symbols
            dic_training["Params"] = node.params
            max_free_symbols = max(max_free_symbols,len(free_symbols))
            max_params = max(max_params,len(node.params))


            dic_training["Map_entry"] = node
            dic_training["In_Memlet"] = [extract_memlet(memlet) for memlet in state.in_edges(tasklet)]
            dic_training["Out_Memlet"] = [extract_memlet(memlet) for memlet in state.out_edges(tasklet)]
            if node in vectorization_map_entry:
                dic_training["Result"] = 1
                #print("Vectorizable")
            else:
                dic_training["Result"] = 0
                #print("Not Vectorizable")
            data_points += [dic_training]
            count += 1
#output = {"max_free_symbols":max_free_symbols,"max_params":max_params,"data":data_points}
with open("/Users/benediktschesch/MyEnv/Vectorization_dic.p", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(data_points)