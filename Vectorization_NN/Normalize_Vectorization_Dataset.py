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
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,
                  symbolic)
from dace.sdfg import has_dynamic_map_inputs
from tqdm import tqdm

def range2list(range,dic_free_symbols):
    text = []
    for rge in range:
        text += [rge.subs(dic_free_symbols)]
    return text

def memlet2dic(memlet,dic_free_symbols):
    result = {}
    result["Dynamic"] = memlet["Dynamic"]
    result["Volume"] = memlet["Volume"].subs(dic_free_symbols)
    result["empty"] = memlet["empty"]
    count = 0
    while "Range"+str(count) in memlet:
        result["Range"+str(count)] = range2list(memlet["Range"+str(count)],dic_free_symbols)
        count += 1
    return result

def map2dic(map,dic_free_symbols,dic_params):
    res = []
    dic = []
    for i in range(len(map.params)):
        dic += [(dic_params[map.params[i]],range2list(map.range[i],dic_free_symbols))]
    return dic

Vectorizations = []

with open("/Users/benediktschesch/MyEnv/Vectorization_dic.p", "rb") as fp:    
    Vectorizations = symbolic.SympyAwareUnpickler(fp).load()

max_symbols = 0
max_params = 0
str_vector = []
result = []
for vec in tqdm(Vectorizations):
    free_symbols = vec["Free_symbols"]
    new_symbols = set()
    new_params = []
    params = vec["Params"]
    dic_params = {}
    dic_free_symbols = {}
    for index,param in enumerate(reversed(params)):
        dic_params[param] = "i"+str(index)
        new_params += ["i"+str(index)]
    count = 0
    for sym in free_symbols:
        if sym in dic_params:
            dic_free_symbols[dace.symbol(sym)] = dic_params[sym]
        else:
            dic_free_symbols[dace.symbol(sym)] = "N"+str(count)
            count += 1
        new_symbols.add(dic_free_symbols[dace.symbol(sym)])
    res_dic = {}
    res_dic["Result"] = vec["Result"]
    res_dic["Params"] = new_params
    res_dic["Free_symbols"] = new_symbols
    res_dic["In_Memlet"] = [memlet2dic(i,dic_free_symbols) for i in vec["In_Memlet"]]
    res_dic["Out_Memlet"] = [memlet2dic(i,dic_free_symbols) for i in vec["Out_Memlet"]]
    res_dic["Map_entry"]  = map2dic(vec["Map_entry"],dic_free_symbols,dic_params)
    result += [res_dic]
    max_symbols = max(max_symbols,count)
    max_params = max(max_params,len(params))


output = {"max_symbols":max_symbols,"max_params":max_params,"data":result}
with open("/Users/benediktschesch/MyEnv/Vectorization_normalized_dic.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(output)








# class Encoder():
#     def __init__(self,length):
#         self.dic = {}
#         count = 9
#         for i in [0,1,2,3,4,5,6,7,8,9]:
#             self.dic[str(i)] = count
#             count += 1
#         self.ops = ["-","~","**","*","+",",","/",":","(",")","ceiling","floor","Mod","Min","Max","int_ceil","int_D"]
#         for i in self.ops:
#             self.dic[i] = count
#             count += 1
#         for i in range(65,65+length):
#             self.dic[chr(i)] = count
#             count+=1
#         self.len = count
    
#     def encode(self,text):
#         if text == "":
#             return []
#         if text[0:1] == " ":
#             return self.encode(text[1:])
#         for i in self.ops:
#             if text.startswith(i):
#                 return [self.dic[i]]+self.encode(text[len(i):])
#         return [self.dic[text[0:1]]]+self.encode(text[1:])

# class Converter:
#     def __init__(self,offset = 0):
#         self.current = offset+65
#         self.dic = dict()

#     def convert(self,string):
#         if string in self.dic:
#             return self.dic[string]
#         else:
#             self.dic[string] = chr(self.current)
#             self.current += 1
#             return self.dic[string]
#     def __len__(self):
#         return len(self.dic)


# # 2, 3: Empty Memlet one hot
# # 4,5: dynamic one hot
# # 6: separator between element of range
# # 7: separator between ranges 
# def encode_memlet(Memlet,encoder):
#     result = []
#     if Memlet["empty"]:
#         return [2]
#     else:
#         result = [3,4+int(Memlet["Dynamic"])]
#     result += encoder.encode(Memlet["Volume"]) 
#     index = 0
#     while ("range"+str(index)) in Memlet:
#         rge = Memlet[("range"+str(index))]
#         result+=encoder.encode(rge[0])+[6]+encoder.encode(rge[1])+[6]+encoder.encode(rge[1])+[7]
#         index+=1
#     return result

# def compute_paths():
#     paths = []
#     for root, dirs, files in os.walk("/Users/benediktschesch/MyEnv"):
#         for file in files:
#             if file.endswith(".sdfg"):
#                 paths.append(os.path.join(root, file))
#     with open("/Users/benediktschesch/MyEnv/Vectorization_paths.txt", "wb") as fp:
#         pickle.dump(paths, fp)

# def compute_dataset(paths):
#     count = 0
#     data_points = []
#     for file in paths:
#         try:
#             sdfg = dace.SDFG.from_file(file)
#         except:
#             print("Not Valid SDFG at: "+str(file))
#             continue
#         dic_training = {}
#         opt = Optimizer(sdfg)
        
#         #state = SDFGState(sdfg.nodes()[0])
#         #for i in opt.get_pattern_matches(patterns=[Vectorization]):
#         #    print(i)
#         vectorization_map_entry = [i.query_node(sdfg.sdfg_list[i.sdfg_id],i._map_entry) for i in opt.get_pattern_matches(patterns=[Vectorization])]
#         for node, state in sdfg.all_nodes_recursive():
#             if isinstance(node, MapEntry):
#                 if has_dynamic_map_inputs(state,node):
#                     continue
                
#                 conv = Converter()
#                 tasklet = state.out_edges(node)[0].dst
#                 if not isinstance(tasklet,Tasklet):
#                     continue
#                 dic_training["Map_entry"] = extract_map(node,conv)
#                 dic_training["In_Memlet"] = [extract_memlet(memlet,conv) for memlet in state.in_edges(tasklet)]
#                 dic_training["In_Memlet"].reverse()
#                 dic_training["Out_Memlet"] = [extract_memlet(memlet,conv) for memlet in state.out_edges(tasklet)]
#                 dic_training["Out_Memlet"].reverse()
#                 if node in vectorization_map_entry:
#                     dic_training["Result"] = 1
#                     print("Vectorizable")
#                 else:
#                     dic_training["Result"] = 0
#                     print("Not Vectorizable")
#                 data_points.append(dic_training)
#                 count = max(count,len(conv))
#     return data_points,count

# X = []
# Y = []
# data_points = []
# paths = []

# #compute_paths()
# with open("/Users/benediktschesch/MyEnv/Vectorization_paths.txt", "rb") as fp:   # Unpickling
#     paths = pickle.load(fp)
# #paths = paths[0:20]
# data_points,count = compute_dataset(paths)
# with open("/Users/benediktschesch/MyEnv/Vectorization_dic.txt", "wb") as fp:
#     pickle.dump(data_points,fp)
# encoder = Encoder(count)
# print("Number of data points: {}".format(len(data_points)))

# # 8: separator between element of range 
# for Vect in data_points:
#     result = []
#     result_map = []
#     result_in_memlet = []
#     result_out_memlet = []
#     index = 0
#     while ("param"+str(index)) in Vect["Map_entry"]:
#         rge = Vect["Map_entry"]["range"+str(index)]
#         encoded_range = encoder.encode(str(rge[0]))+[8]+encoder.encode(str(rge[1]))+[8]+encoder.encode(str(rge[1]))
#         result_map+=encoder.encode(Vect["Map_entry"]["param"+str(index)])+[0]+encoded_range+[1]
#         index+=1
#     #result += [3]
#     #if len(Vect["In_Memlet"]) == 0:
#         #result_in_memlet += [0]
#     for i in Vect["In_Memlet"]:
#         result_in_memlet += encode_memlet(i,encoder)
#     #result += [4]
#     #if len(Vect["Out_Memlet"]_ == 0:
#         #result_out_memlet += [0]
#     for i in Vect["Out_Memlet"]:
#         result_out_memlet += encode_memlet(i,encoder)
#     X.append([[np.array(result_in_memlet),np.array(result_map),np.array(result_out_memlet)],int(Vect["Result"])])
# #print("Positive rate: {}%".format(num_positive*100.0/len(X)))

# with open("/Users/benediktschesch/MyEnv/Vectorization_data.txt", "wb") as fp:
#     pickle.dump(X, fp)