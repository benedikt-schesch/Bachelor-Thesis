from aenum import convert
import dace
import dace.subsets
from dace.transformation.dataflow import vectorization
import numpy as np
import os, glob
import tensorflow as tf
from tensorflow import keras
import matplotlib as plt
import networkx as nx
from networkx.algorithms import isomorphism as iso
from typing import Dict, Iterator, List, Tuple, Type, Union
from dace.transformation.transformation import Transformation
from sklearn.model_selection import train_test_split
import random
from dace.sdfg import nodes, SDFG, propagation
import re
import torch.nn as nn
import torch
from torch.utils.data import TensorDataset, DataLoader, Dataset
from torch import empty, optim
import pickle
from dace.sdfg.graph import MultiConnectorEdge
from dace.sdfg.nodes import AccessNode, MapEntry, MapExit, NestedSDFG, Tasklet, ConsumeEntry,ConsumeExit
from dace.transformation.optimizer import Optimizer
from dace.transformation.dataflow import Vectorization
from dace.sdfg.state import SDFGState
from dace.sdfg import has_dynamic_map_inputs
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from tqdm import tqdm
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import extract_map,extract_memlet

def compute_paths():
    paths = []
    for root, dirs, files in tqdm(os.walk("/Users/benediktschesch/MyEnv")):
        for file in files:
            if file.endswith(".sdfg"):
                paths.append(os.path.join(root, file))
    with open("/Users/benediktschesch/MyEnv/temp/Vectorization_paths.pkl", "wb") as fp:
        pickle.dump(paths, fp)
paths = []
compute_paths()
with open("/Users/benediktschesch/MyEnv/temp/Vectorization_paths.pkl", "rb") as fp:   # Unpickling
    paths = pickle.load(fp)
#paths = paths[0:20]
count = 0
data_points = []
max_free_symbols = 0
max_params = 0
rejected_consume = 0
rejected_dynamic = 0
positive_results = 0
total_results = 0
#test_8
#paths = ['/Users/benediktschesch/MyEnv/tests/.dacecache/test1/program.sdfg']
for file in tqdm(paths):
    try:
        sdfg = dace.SDFG.from_file(file)
    except:
        print("Not Valid SDFG at: "+str(file))
        continue
    opt = Optimizer(sdfg)
    vectorization_tasklet = [i.query_node(sdfg.sdfg_list[i.sdfg_id],i._tasklet) for i in opt.get_pattern_matches(patterns=[Vectorization])]
    for state in sdfg.states():
        free_symbols = set({})
        params = set({})
        nodes = []
        node_to_idx = {}
        G = nx.Graph()
        valid = False
        for count,node in enumerate(state.nodes()):
            nodes += [(count,{"attr": node})]
            node_to_idx[node] = count
        G.add_nodes_from(nodes)
        for edge in state.edges():
            G.add_edge(node_to_idx[edge._src],node_to_idx[edge._dst],attr = edge)
        
        pos_res = 0
        tot_res = 0
        for edge in G.edges(data = True):
            free_symbols.update(edge[2]['attr'].data.free_symbols)
            edge[2]['attr'] = extract_memlet(edge[2]['attr'])
        for node in G.nodes(data = True):
            free_symbols.update(node[1]["attr"].free_symbols)
            if isinstance(node[1]["attr"],MapEntry):
                if has_dynamic_map_inputs(state,node[1]["attr"]):
                    valid = False
                    rejected_dynamic += 1
                    break
                params.update(node[1]["attr"].params)
                node[1]["attr"] = {"data":extract_map(node[1]["attr"]),"Type":"MapEntry"}
            elif isinstance(node[1]["attr"], MapExit):
                node[1]["attr"] = {"Type":"MapExit"}
            elif isinstance(node[1]["attr"], AccessNode):
                node[1]["attr"] = {"data":node[1]["attr"].data,"Type":"AccessNode"}
            elif isinstance(node[1]["attr"],Tasklet):
                valid = True
                tot_res += 1
                if node[1]["attr"] in vectorization_tasklet:
                    node[1]["attr"] = {"Type":"Tasklet","Result":1}
                    pos_res += 1
                else:
                    node[1]["attr"] = {"Type":"Tasklet","Result":0}
            elif isinstance(node[1]["attr"],NestedSDFG):
                node[1]["attr"] = {"Type":"NestedSDFG"}
            elif isinstance(node[1]["attr"],ConsumeEntry) or isinstance(node[1]["attr"],ConsumeExit):
                valid = False
                rejected_consume += 1
                break
            else:
                valid = False
                print("Uknown type of node: ",node)
                break
        if valid:
            positive_results += pos_res
            total_results += tot_res
            max_free_symbols = max(max_free_symbols,len(free_symbols.difference(params)))
            data_points.append({"G":G,"free_symbols":free_symbols.difference(params),"params":params,"file": file})
            max_params = max(len(params),max_params)
output = {"max_free_symbols":max_free_symbols,"max_params":max_params,"data":data_points}
with open("/Users/benediktschesch/MyEnv/temp/Vect_graphs_raw.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(output)