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
from pathlib import Path
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import extract_map,extract_memlet

#Compute and store paths in which an SDFG is present
def compute_paths():
    paths = []
    for root, dirs, files in tqdm(os.walk("/Users/benediktschesch/MyEnv")):
        for file in files:
            if file.endswith(".sdfg"):
                paths.append(os.path.join(root, file))
    with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "wb") as fp:
        pickle.dump(paths, fp)
paths = []

#Load SDFG paths
my_file = Path("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl")
if not my_file.is_file():
    compute_paths()
with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "rb") as fp:
    paths = pickle.load(fp)
#paths = paths[0:20]

#Metadata Initialization
count = 0
data_points = []
max_free_symbols = 0
max_params = 0

#Define transformations to analyze
transformations_tasklet = [Vectorization]
transformations_map_entry = []


#Itterate over all files
for file in tqdm(paths):
    try:
        file_sdfg = dace.SDFG.from_file(file)
    except:
        print("Not Valid SDFG at: "+str(file))
        continue
    
    #Itterate over all SDFGS
    for sdfg in file_sdfg.all_sdfgs_recursive():
        opt = Optimizer(sdfg)
        
        #Itterate over all states
        for state in sdfg.states():
            #Initialize Metadata
            free_symbols = set({})
            params = set({})
            nodes = []
            node_to_idx = {}
            G = nx.Graph()
            valid = False
            trans_dic = {}

            #Compute possible transformation points
            for trans in transformations_tasklet:
                trans_dic[trans] = {"results":[],"data_points":[],"nodes":[i.query_node(sdfg.sdfg_list[i.sdfg_id],i._tasklet) for i in opt.get_pattern_matches(patterns=transformations_tasklet)]}
            for trans in transformations_map_entry:
                trans_dic[trans] = {"results":[],"data_points":[],"nodes":[i.query_node(sdfg.sdfg_list[i.sdfg_id],i._map_entry) for i in opt.get_pattern_matches(patterns=transformations_map_entry)]}
            
            #Create Graph in networkx
            for count,node in enumerate(state.nodes()):
                nodes += [(count,{"attr": node})]
                node_to_idx[node] = count
            G.add_nodes_from(nodes)
            for edge in state.edges():
                G.add_edge(node_to_idx[edge._src],node_to_idx[edge._dst],attr = edge)
            
            #Extract Memlet data
            for edge in G.edges(data = True):
                free_symbols.update(edge[2]['attr'].data.free_symbols)
                edge[2]['attr'] = extract_memlet(edge[2]['attr'])
            
            #Extract Node data and Transformation
            for node in G.nodes(data = True):
                free_symbols.update(node[1]["attr"].free_symbols)
                if isinstance(node[1]["attr"],MapEntry):
                    if has_dynamic_map_inputs(state,node[1]["attr"]):
                        valid = False
                        break
                    for trans in transformations_map_entry:
                        trans_dic[trans]["data_points"].append(node[0])
                        trans_dic[trans]["results"].append(node[1]["attr"] in trans_dic[trans]["nodes"])
                    params.update(node[1]["attr"].params)
                    node[1]["attr"] = {"data":extract_map(node[1]["attr"]),"Type":"MapEntry"}
                elif isinstance(node[1]["attr"], MapExit):
                    node[1]["attr"] = {"Type":"MapExit"}
                elif isinstance(node[1]["attr"], AccessNode):
                    node[1]["attr"] = {"data":node[1]["attr"].data,"Type":"AccessNode"}
                elif isinstance(node[1]["attr"],Tasklet):
                    valid = True
                    for trans in transformations_tasklet:
                        trans_dic[trans]["data_points"].append(node[0])
                        trans_dic[trans]["results"].append(node[1]["attr"] in trans_dic[trans]["nodes"])
                elif isinstance(node[1]["attr"],NestedSDFG):
                    node[1]["attr"] = {"Type":"NestedSDFG"}
                elif isinstance(node[1]["attr"],ConsumeEntry) or isinstance(node[1]["attr"],ConsumeExit):
                    valid = False
                    break
                else:
                    valid = False
                    print("Uknown type of node: ",node)
                    break
                
            #Compute possible transformation points
            for trans in transformations_tasklet:
                del trans_dic[trans]["nodes"]
            for trans in transformations_map_entry:
                del trans_dic[trans]["nodes"]
            
            #Add graph if valid
            if valid:
                max_free_symbols = max(max_free_symbols,len(free_symbols.difference(params)))
                data_points.append({"G":G,"free_symbols":free_symbols.difference(params),\
                    "params":params,"file": file,"transformations":trans_dic})
                max_params = max(len(params),max_params)
#Store output
output = {"max_free_symbols":max_free_symbols,"max_params":max_params,"data":data_points}
with open("/Users/benediktschesch/MyEnv/temp/Graphs_raw.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(output)