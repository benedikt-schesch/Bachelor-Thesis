#!/usr/bin/env python3
#
#Find all the SDFGs in our computer, extract them and convert them to a networkx structure
#
import time,os,pickle
import dace
from sympy.core.numbers import Integer
import copy
import statistics
from dace.config import Config
from dace.sdfg import SDFG, SDFGState
from dace.sdfg import graph as gr, nodes as nd
import dace.subsets
import itertools
from dace.data import Array, Scalar
from dace.transformation.dataflow import vectorization
import numpy as np
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
import sys

#RUN: DACE_report_each_invocation=0

path_to_sdfg = "/Users/benediktschesch/MyEnv/GNN_RL2/SDFGS"
size_of_inputs = 2048  

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
    for root, dirs, files in tqdm(os.walk(path_to_sdfg)):
        for file in files:
            if file.endswith(".sdfg"):
                paths.append(os.path.join(root, file))
    #with open("/Users/benediktschesch/MyEnv/temp/sdfg_paths.pkl", "wb") as fp:
        #pickle.dump(paths, fp)
    return paths

paths = compute_paths()
#Metadata Initialization
size = [1,4,16,64,256,1024]


#Itterate over all SDFGS
for path in paths:
    try:
        graph = dace.SDFG.from_file(path)
        for sdfg in graph.all_sdfgs_recursive():
            #Itterate over all states
            print(sdfg)
            for index,state in enumerate(sdfg.states()):
                results = {}
                for index2,node in enumerate(state.nodes()):
                    if isinstance(node,MapEntry):
                        timings = []
                        somelists = [size for i in node.params]
                        for tilling in itertools.product(*(somelists)):
                            invalid = True
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
                            new_map_entry = optim_sdfg.node(index).entry_node(entry)
                            new_map_entry.instrument = dace.InstrumentationType.Timer
                            try:
                                optim_sdfg.clear_instrumentation_reports()
                            except Exception:
                                pass
                            try:
                                run_sdfg(optim_sdfg)
                            except Exception:
                                valid = False
                                break
                            timings.append({"tilling":tilling,\
                                "time":[next(iter(i.durations.values()))[0] for i in optim_sdfg.get_instrumentation_reports()]})
                        sdfg.node(index).node(index2).instrument = dace.InstrumentationType.Timer
                        try:
                            sdfg.clear_instrumentation_reports()
                        except Exception:
                            pass
                        try:
                            run_sdfg(sdfg)
                        except Exception:
                            valid = False
                            break
                        timings.insert(0,{"time":[next(iter(i.durations.values()))[0] for i in optim_sdfg.get_instrumentation_reports()]})
                        results[(index,index2)] = timings
            with open(path_to_sdfg+"/"+path.split("/")[-1][:-5]+"_info.pkl", "wb") as fp:
                pickle.dump(results, fp)
    except Exception:
        pass