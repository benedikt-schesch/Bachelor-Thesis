#
#Find all the SDFGs in our computer, extract them and convert them to a networkx structure
#
from pickle import MARK
from aenum import convert
from numpy.lib.arraysetops import isin
import dace
from dace.config import Config
from dace.sdfg import SDFG, SDFGState
from dace.sdfg import graph as gr, nodes as nd
import networkx as nx
from networkx.algorithms import isomorphism as iso
from typing import Dict, Iterator, List, Tuple, Type, Union
from dace.transformation.transformation import Transformation
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
from dace.transformation.pattern_matching import collapse_multigraph_to_nx,type_match
from dace.transformation.dataflow import MapInterchange,Vectorization, MapTiling, DoubleBuffering, MapFusion, MapExpansion
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
#transforms = [(MapFusion,[(MapExit,"_first_map_exit"),(MapEntry,"_second_map_entry")]),(Vectorization,[(Tasklet,"_tasklet")])]
#transforms = [(MapFusion,[(MapExit,"_first_map_exit"),(MapEntry,"_second_map_entry")])]
#transforms = [(Vectorization,[(Tasklet,"_tasklet")])]
#transforms = [(MapFusion,[(MapExit,"_first_map_exit"),(MapEntry,"_second_map_entry")]),\
    # (Vectorization,[(Tasklet,"_tasklet")]),\
    # (MapExpansion,[(MapEntry,"_map_entry")]),\
    # (MapInterchange,[(MapEntry,"_outer_map_entry"),(MapEntry,"_inner_map_entry")])]
transforms = [(Vectorization,[Vectorization._tasklet]),\
    (MapFusion,[MapFusion._first_map_exit,MapFusion._second_map_entry]),\
        (MapExpansion,[MapExpansion._map_entry]),\
        (MapInterchange,[MapInterchange._outer_map_entry,MapInterchange._inner_map_entry])]

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
        for i in range(1):
            
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
                critical = False


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
                        critical = True
                        break
                    for (a,b) in [(u,v),(v,u),(u,edge),(v,edge),(edge,u),(edge,v)]:
                        if (dic_node[a],dic_node[b]) not in adj_lists[type_dic[type(edge._src)]]:
                            adj_lists[type_dic[type(edge._src)]].append((dic_node[a],dic_node[b]))
                    list_nodes += [edge]
                    count += 1
                if critical:
                    break

                #Create free symbol dictionary
                for counter,sym in enumerate(list(free_symbols.difference(params))):
                    freesymbol_dic[dace.symbol(sym)] = "N"+str(counter)

                for node in list_nodes:
                    if isinstance(node,MapEntry):
                        map_entry.append(dic_node[node])
                        if has_dynamic_map_inputs(state,node):
                            critical = True
                            break
                        nodes_str.append({"Type":"MapEntry","data":map2str(map2dic(extract_map(node),freesymbol_dic,str_params_dic))})
                    elif isinstance(node,Tasklet):
                        tasklet.append(dic_node[node])
                        nodes_str.append({"Type":type(node).__name__})
                    elif isinstance(node,MultiConnectorEdge):
                        nodes_str.append({"Type":"Memlet","data":mem2str(memlet2dic(extract_memlet(node),freesymbol_dic))})
                    elif isinstance(node,(MapExit,NestedSDFG,AccessNode)):
                        nodes_str.append({"Type":type(node).__name__})
                    elif isinstance(node,ConsumeEntry) or isinstance(node,ConsumeExit):
                        critical = True
                        break
                    else:
                        critical = True
                        print("Uknown type of node: ",node)
                        break
                if critical:
                    break

                list_transform_points = [{"results":[],"points":[]} for _ in transforms]
                for i in range(len(transforms)):
                    pattern = transforms[i][0]
                    node_match=type_match
                    edge_match=None
                    strict=False
                    digraph = collapse_multigraph_to_nx(state)
                    for idx, expression in enumerate(pattern.expressions()):
                        cexpr = collapse_multigraph_to_nx(expression)
                        graph_matcher = iso.DiGraphMatcher(digraph,
                                            cexpr,
                                            node_match=node_match,
                                            edge_match=edge_match)
                        for subgraph in graph_matcher.subgraph_isomorphisms_iter():
                            subgraph = {
                                cexpr.nodes[j]['node']: state.node_id(digraph.nodes[i]['node'])
                                for (i, j) in subgraph.items()
                            }
                            match_found = pattern.can_be_applied(state,
                                                     subgraph,
                                                     idx,
                                                     sdfg,
                                                     strict=strict)
                            point = []
                            for elems in transforms[i][1]:
                                point.append(dic_node[state.nodes()[subgraph[elems]]])
                            try:
                                match_found = pattern.can_be_applied(state,
                                                                    subgraph,
                                                                    idx,
                                                                    sdfg,
                                                                    strict=strict)
                            except Exception as e:
                                if Config.get_bool('optimizer', 'match_exception'):
                                    raise
                                match_found = False
                            valid = True
                            list_transform_points[i]["results"].append(int(match_found))
                            list_transform_points[i]["points"].append(point)


                
                #Add graph if valid
                if valid:
                    max_free_symbols = max(max_free_symbols,len(free_symbols.difference(params)))
                    data_points.append({"G":{"adjacency_lists":adj_lists,"node_data":nodes_str},"file": file,
                        "list_trans": list_transform_points})
                    max_num_param = max(len(params),max_num_param)
                    max_num_map_entry = max(max_num_map_entry,num_map_entry)
                #sdfg.apply_transformations_repeated(MapExpansion)


#Store output
output = {"data":data_points,"max_num_param":max_num_param,"max_free_symbols":max_free_symbols, \
    "max_num_map_entry": max_num_map_entry,"transforms": transforms}
with open("/Users/benediktschesch/MyEnv/temp/Normalized_data.pkl", "wb") as fp:
    pickle.dump(output,fp)