#
#Find all the SDFGs in our computer, extract them and convert them to a networkx structure
#
from pickle import MARK
from aenum import convert
from numpy.lib.arraysetops import isin
import dace
from sympy.core.numbers import Integer
import copy
import subprocess
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
from dace.config import Config
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


assert Config.get_bool('profiling')
# from signal import signal, SIGSEGV
# def handler( sigNum, frame ):
#   print( "handle signal", sigNum )
# signal(SIGSEGV, handler)


file_interm_store = "/Users/benediktschesch/MyEnv/temp/temp_store_sdfgs"
temp_path_sdfg = '/Users/benediktschesch/MyEnv/temp/sdfggraphs/'
use_temp_storage = True
size_of_inputs = 2048

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
    

def run_sdfg(sdfg: SDFG):
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




paths = []
#Load SDFG paths
my_file = Path("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl")
if not my_file.is_file():
    compute_paths()
with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "rb") as fp:
    paths = pickle.load(fp)

#Metadata Initialization
count = 0
data_points = []
max_free_symbols = 0
max_params = 0
max_num_map_entry = 0
max_num_param = 0


size = [1,4,16,64,256,1024]
#paths = ["/Users/benediktschesch/MyEnv/tests/.dacecache/test233/program.sdfg"]
paths.remove("/Users/benediktschesch/MyEnv/tests/.dacecache/test14/test/program.sdfg")
paths.remove("/Users/benediktschesch/MyEnv/tests/.dacecache/test149/program.sdfg")
max_id = 0

if use_temp_storage:
    for root, dirs, files in tqdm(os.walk(temp_path_sdfg)):
        for file in files:
            max_id = max(max_id,int(file[:-4])+1)
            with open(temp_path_sdfg+file, "rb") as fp:
                try:
                    raw_data = pickle.load(fp)
                except Exception:
                    continue
            if use_temp_storage and raw_data["file"] in paths:
                paths.remove(raw_data["file"])
                data_points += raw_data["data"]
                max_free_symbols = max(max_free_symbols,raw_data["max_free_symbols"])
                max_num_map_entry = max(max_num_map_entry,raw_data["max_num_map_entry"])
                max_num_param = max(max_num_param,raw_data["max_num_param"])
max_id += 1
#paths.remove("/Users/benediktschesch/.dacecache/mapreduce_twomaps/program.sdfg")
#paths = [paths[0]]+["/Users/benediktschesch/MyEnv/tests/transformations/.dacecache/operation/program.sdfg"]
#Itterate over all files
#paths = ["/Users/benediktschesch/MyEnv/tests/transformations/.dacecache/test144/program.sdfg"]
#paths = ["/Users/benediktschesch/MyEnv/tests/.dacecache/test60/program.sdfg"]
for id,file in tqdm(enumerate(paths)):
    my_file = Path(file)
    if not my_file.is_file():
        continue
    print("Num ",id,"/",len(paths)," FILE:",file)
    tempfile = Path(str(temp_path_sdfg)+str(max_id+id)+".pkl")
    try:
        subprocess.call(["python",'/Users/benediktschesch/MyEnv/GNN_RL/sdfg_to_graph_file_script.py',\
            file,temp_path_sdfg,\
            str(id+max_id),str(size_of_inputs)],timeout=100*60)
    except Exception:
        pass
    if not tempfile.is_file():
        continue
    with open(tempfile, "rb") as fp:
        try:
            raw_data = pickle.load(fp)
        except Exception:
            continue
    data_points += raw_data["data"]
    max_free_symbols = max(max_free_symbols,raw_data["max_free_symbols"])
    max_num_map_entry = max(max_num_map_entry,raw_data["max_num_map_entry"])
    max_num_param = max(max_num_param,raw_data["max_num_param"])

    
#Store output
output = {"data":data_points,"max_num_param":max_num_param,"max_free_symbols":max_free_symbols, \
    "max_num_map_entry": max_num_map_entry,"size":size}
with open("/Users/benediktschesch/MyEnv/temp/Normalized_data.pkl", "wb") as fp:
    pickle.dump(output,fp)