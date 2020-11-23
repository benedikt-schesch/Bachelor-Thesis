#
#Find all the SDFGs in our computer, extract them and convert them to a networkx structure
#
from pickle import MARK
from aenum import convert
from numpy.lib.arraysetops import isin
import dace
import dace.subsets
import itertools
from dace.transformation.dataflow import vectorization
import numpy as np
import os, glob
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt
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
from dace.transformation.dataflow import Vectorization, MapTiling, DoubleBuffering, MapFusion
from dace.sdfg.state import SDFGState
from dace.sdfg import has_dynamic_map_inputs
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from tqdm import tqdm
from pathlib import Path
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import extract_map,extract_memlet,memlet2dic,map2dic,mem2str,map2str

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
max_num_map_entry = 0
max_num_param = 0


#Transform
#(MapFusion,[(MapExit,"_first_map_exit"),(MapEntry,"_second_map_entry")])  
#transforms = [(MapFusion,[(MapExit,"_first_map_exit"),(MapEntry,"_second_map_entry")])]
transforms = [(Vectorization,[(Tasklet,"_tasklet")])]
#Define transformations to analyze
transformations_tasklet = []
transformations_map_entry = [MapFusion]

type_dic = {}
type_dic[MultiConnectorEdge] = 1
type_dic[AccessNode] = 2
type_dic[MapEntry] = 3
type_dic[MapExit] = 4
type_dic[Tasklet] = 4
type_dic[NestedSDFG] = 5

#Itterate over all files
for file in tqdm(paths):
    try:
        file_sdfg = dace.SDFG.from_file(file)
    except:
        print("Not Valid SDFG at: "+str(file))
        continue
    
    #Itterate over all SDFGS
    for sdfg in file_sdfg.all_sdfgs_recursive():
        #sdfg.apply_transformations_repeated(MapExpansion)
        
        opt = Optimizer(sdfg)
        
        #Itterate over all states
        for state in sdfg.states():
            #Skip empty states
            if len(state.nodes()) == 0:
                continue
            #Initialize Metadata
            free_symbols = set({})
            params = set({})
            nodes = state.nodes()
            nodes_str = []
            valid = False
            map_entry = []
            tasklet = []
            count = 0
            dic_node = {}
            adj_lists = [[],[],[],[],[],[],[]]
            str_params_dic = {}
            freesymbol_dic = {}
            num_map_entry = 0
            list_nodes = []
            critical = True



            list_transform_points = [{"results":[],"points":[[] for i in range(len(b))]}\
                 for (_,b) in transforms]
            
            for i,(_,elems) in enumerate(transforms):
                for j,(typ,_) in enumerate(elems):
                    for candidate in state.nodes()+state.edges():
                        if isinstance(candidate,typ):
                            list_transform_points[i]["points"][j].append(candidate)
            for trans in list_transform_points:
                trans["points"] = [list(i) for i in itertools.product(*trans["points"])]
            
            list_transforms = [[[i.query_node(sdfg.sdfg_list[i.sdfg_id],i.__getattribute__(b)) \
                for (_,b) in ls] for i in \
                opt.get_pattern_matches(patterns=[trans])] for \
                        (trans,ls) in transforms]

            for j,trans in enumerate(list_transform_points):
                for i,candidate in enumerate(trans["points"]):
                    if candidate in list_transforms[j]:
                        trans["results"].append(1)
                    else:
                        trans["results"].append(0)


            for node in state.nodes():
                free_symbols.update(node.free_symbols)
                dic_node[node] = count
                adj_lists[0] += [(count,count)]
                if isinstance(node,MapEntry):
                    params.update(node.params)
                    for i,param in enumerate(reversed(node.params)):
                        str_params_dic[param] = "i"+str(num_map_entry)+str(i)
                        freesymbol_dic[dace.symbol(param)] = "i"+str(num_map_entry)+str(i)
                    max_num_param = max(max_num_param,len(node.params))
                    num_map_entry += 1
                    ex = state.exit_node(node)
                    if ex in dic_node:
                        adj_lists[type_dic[MapExit]] += [(dic_node[ex],count)]
                        adj_lists[type_dic[MapEntry]] += [(count,dic_node[ex])]
                if isinstance(node,MapExit):
                    entry = state.entry_node(node)
                    if entry in dic_node:
                        adj_lists[type_dic[MapEntry]] += [(dic_node[entry],count)]
                        adj_lists[type_dic[MapExit]] += [(count,dic_node[entry])]
                count += 1
                list_nodes += [node]

            for edge in state.edges():
                free_symbols.update(edge.data.free_symbols)
                u = edge._src
                v = edge._dst
                adj_lists[0] += [(count,count)]
                dic_node[edge] = count
                if type(u) not in type_dic or type(v) not in type_dic:
                    critical = False
                    break
                for (a,b) in [(u,v),(v,u),(u,edge),(v,edge),(edge,u),(edge,v)]:
                    if (dic_node[a],dic_node[b]) not in adj_lists[type_dic[type(edge._src)]]:
                        adj_lists[type_dic[type(edge._src)]].append((dic_node[a],dic_node[b]))
                list_nodes += [edge]
                count += 1
            if not critical:
                break
            for j,trans in enumerate(list_transform_points):
                for i,candidate in enumerate(trans["points"]):
                    trans["points"][i] = [dic_node[elem] for elem in candidate]

            #Create free symbol dictionary
            for counter,sym in enumerate(list(free_symbols.difference(params))):
                freesymbol_dic[dace.symbol(sym)] = "N"+str(counter)

            for node in list_nodes:
                if isinstance(node,MapEntry):
                    map_entry.append(dic_node[node])
                    if has_dynamic_map_inputs(state,node):
                        valid = False
                        break
                    valid = True
                    nodes_str.append({"Type":"MapEntry","data":map2str(map2dic(extract_map(node),freesymbol_dic,str_params_dic))})
                elif isinstance(node,Tasklet):
                    tasklet.append(dic_node[node])
                    valid = True
                    nodes_str.append({"Type":type(node).__name__})
                elif isinstance(node,MultiConnectorEdge):
                    nodes_str.append({"Type":"Memlet","data":mem2str(memlet2dic(extract_memlet(node),freesymbol_dic))})
                elif isinstance(node,(MapExit,NestedSDFG,AccessNode)):
                    nodes_str.append({"Type":type(node).__name__})
                elif isinstance(node,ConsumeEntry) or isinstance(node,ConsumeExit):
                    valid = False
                    break
                else:
                    valid = False
                    print("Uknown type of node: ",node)
                    break

            #Add graph if valid
            if valid:
                max_free_symbols = max(max_free_symbols,len(free_symbols.difference(params)))
                data_points.append({"G":{"adjacency_lists":adj_lists,"node_data":nodes_str},"file": file,
                    "list_trans": list_transform_points})
                max_num_param = max(len(params),max_num_param)
                max_num_map_entry = max(max_num_map_entry,num_map_entry)


#Store output
output = {"data":data_points,"max_num_param":max_num_param,"max_free_symbols":max_free_symbols, \
    "max_num_map_entry": max_num_map_entry,"transforms": transforms}
with open("/Users/benediktschesch/MyEnv/temp/Normalized_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(output)