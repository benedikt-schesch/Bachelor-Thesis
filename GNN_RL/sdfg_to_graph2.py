#!/usr/bin/env python3
#
#Find all the SDFGs in our computer, extract them and convert them to a networkx structure
#
from pickle import MARK
from aenum import convert
from numpy.lib.arraysetops import isin
import dace
from sympy.core.numbers import Integer
import copy
import statistics
from dace.config import Config
from dace.sdfg import SDFG, SDFGState
from dace.sdfg import graph as gr, nodes as nd
import networkx as nx
from networkx.algorithms import isomorphism as iso
from typing import Dict, Iterator, List, Tuple, Type, Union
from dace.transformation.transformation import Transformation
import dace.subsets
import itertools
from dace.data import Array, Scalar
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
from dace.transformation.dataflow import InLocalStorage,OutLocalStorage,MapInterchange,Vectorization, MapTiling, DoubleBuffering, MapFusion, MapExpansion
from dace.sdfg.state import SDFGState
from dace.sdfg import has_dynamic_map_inputs
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from tqdm import tqdm
from pathlib import Path
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import extract_map,extract_memlet,memlet2dic,map2dic,mem2str,map2str

def enum_one_hot(size):
    res = [[0]*size for i in range(size)]
    for i in range(len(res)):
        res[i][i] = 1
    return res

def measure_run_time():
    with open('results.log', 'r') as f:
        lines = f.readlines()
    times = []
    for line in lines[1:]:
        times.append(float(str.split(line, sep='\t')[-1][:-1]))
    return statistics.median(times)
    

def run_sdfg(size_of_inputs,sdfg: SDFG):
    compiled = sdfg.compile()
    dic = {}
    for k in sdfg.arglist():
        v2 = sdfg.arglist()[k]
        if isinstance(v2,Array):
            if not v2.transient:
                if isinstance(v2,Scalar):
                    dic[k] = v2.dtype()
                elif isinstance(v2,Array):
                    args = []
                    for i in enumerate(v2.shape):
                        if not isinstance(i,Integer):
                            args.append(size_of_inputs)
                        else:
                            args.append(i)
                    dic[k] = np.random.rand(*(tuple(args))).astype(v2.dtype())
                else:
                    print(v2)
        elif isinstance(v2,Scalar):
            dic[k] = size_of_inputs
    compiled(**dic)

#Compute and store paths in which an SDFG is present
def compute_paths():
    paths = []
    for root, dirs, files in tqdm(os.walk("/Users/benediktschesch/MyEnv")):
        for file in files:
            if file.endswith(".sdfg"):
                paths.append(os.path.join(root, file))
    with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "wb") as fp:
        pickle.dump(paths, fp)


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
transforms = [(Vectorization,[Vectorization._map_entry,Vectorization._tasklet,Vectorization._map_exit]),\
    (MapFusion,[MapFusion.first_map_exit,MapFusion.second_map_entry]),\
        (MapExpansion,[MapExpansion.map_entry]),\
        (MapInterchange,[MapInterchange.outer_map_entry,MapInterchange.inner_map_entry])]

type_dic = {}
type_dic[MultiConnectorEdge] = 1
type_dic[AccessNode] = 2
type_dic[MapEntry] = 3
type_dic[MapExit] = 4
type_dic[Tasklet] = 4
type_dic[NestedSDFG] = 5
size = [1,4,16,64,256,1024]
def comp(file,size_of_inputs,output):
    #Metadata Initialization
    type_dic = {}
    type_dic[MultiConnectorEdge] = 1
    type_dic[AccessNode] = 2
    type_dic[MapEntry] = 3
    type_dic[MapExit] = 4
    type_dic[Tasklet] = 4
    type_dic[NestedSDFG] = 5
    size = [1,4,16,64,256,1024]
    count = 0
    data_points = []
    max_free_symbols = 0
    max_params = 0
    max_num_map_entry = 0
    max_num_param = 0
    try:
        file_sdfg = dace.SDFG.from_file(file)
    except:
        sys.exit()
    #Itterate over all SDFGS
    for sdf in file_sdfg.all_sdfgs_recursive():
        for augment in range(1):
            #Itterate over all states
            for index,state in enumerate(sdf.states()):
                sdfg = copy.deepcopy(sdf)
                #Skip empty states
                if len(state.nodes()) == 0:
                    continue
                #Initialize Metadata
                free_symbols = set({})
                params = set({})
                nodes = state.nodes()
                nodes_str = []
                valid = True
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
                    continue

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
                    continue
                

                results = []
                for index2,node in enumerate(state.nodes()):
                    if isinstance(node,MapEntry) and valid:
                        till_perf_min = sys.float_info.max
                        till = 0
                        localstorein = [enum_one_hot(len(node.params)+1) for i in node._in_connectors]
                        localstoreout = [enum_one_hot(len(node.params)+1) for i in node._out_connectors]
                        somelists = [size for i in node.params]
                        #or instorage in itertools.product(*localstorein):
                            #for outstorage in itertools.product(*localstoreout):
                        for tilling in itertools.product(*(somelists)):
                            invalid = True
                            #for param in range(len(node.params)):
                                #for array in instorage+outstorage:
                                    #if array[param] == 1 and tilling[param] == 0:
                                        #invalid = True
                            for i in tilling:
                                if i != 1:
                                    invalid = False
                            if invalid:
                                continue
                            optim_sdfg = copy.deepcopy(sdfg)
                            entry = optim_sdfg.node(index).node(index2)
                            MapTiling.apply_to(optim_sdfg,\
                                _map_entry=entry,\
                                options = {"tile_sizes": tilling})
                            #new_map_entry = optim_sdfg.node(index).entry_node(entry)
                            #new_map_entry.instrument = dace.InstrumentationType.Timer
                            #optim_sdfg.node(index).scope_subgraph(new_map_entry)
                            #new_map_exit = optim_sdfg.node(index).exit_node(new_map_entry)
                            #next(iter(optim_sdfg.get_latest_report().entries.values()))[0]
                            #new_map_entry = optim_sdfg.states()[index].nodes()[-2]
                            try:
                                run_sdfg(size_of_inputs,optim_sdfg)
                            except Exception:
                                valid = False
                                break
                            time = measure_run_time()
                            if time < till_perf_min:
                                till = tilling
                                till_perf_min = time
                        try:
                            run_sdfg(size_of_inputs,sdfg)
                        except Exception:
                            valid = False
                            break
                        time = measure_run_time()
                        if time < till_perf_min:
                            till = [1 for i in node.params]
                            till_perf_min = time
                        results.append([index2,len(node.params),list(till)])


                #Add graph if valid
                if valid:
                    max_free_symbols = max(max_free_symbols,len(free_symbols.difference(params)))
                    data_points.append({"G":{"adjacency_lists":adj_lists,"node_data":nodes_str},"file": file,
                        "results": results})
                    max_num_param = max(len(params),max_num_param)
                    max_num_map_entry = max(max_num_map_entry,num_map_entry)

    #Store output
    out = {"data":data_points,"max_num_param":max_num_param,"max_free_symbols":max_free_symbols, \
        "max_num_map_entry": max_num_map_entry,"size":size,"file":file}
    output.put(out)


import multiprocessing as mp
import random
import string


paths = []
#Load SDFG paths
my_file = Path("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl")
if not my_file.is_file():
    compute_paths()
with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "rb") as fp:
    paths = pickle.load(fp)

# Define an output queue
output = mp.Queue()

paths = paths[4:15]
# Setup a list of processes that we want to run
processes = [mp.Process(target=comp, args=(path, 2048,output)) for path in paths]

print("Starting processes")
# Run processes
for p in processes:
    p.start()

print("Waiting for processes to finish")
# Exit the completed processes
for p in processes:
    p.join()

print("Processes finished")
# Get process results from the output queue
results = [output.get() for p in processes]

print(results)