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
from dace import (data as dt, memlet as mm, subsets as sbs, dtypes, properties,symbolic)
from dace.sdfg import has_dynamic_map_inputs
from tqdm import tqdm
def range2str(rge):
    return str(rge[0])+"RANGESEP"+str(rge[1])+"RANGESEP"+str(rge[2])

def mem2str(memlet):
    if memlet["empty"]:
        return "EMPTYMEMLET"
    text = str(int(memlet["Dynamic"]))
    text += "MEMSEP1"
    text += str(memlet["Volume"])
    text += "MEMSEP2"
    count = 0
    while "Range"+str(count) in memlet:
        text += range2str(memlet["Range"+str(count)])+"MEMSEP3"
        count += 1
    return text

class Encoder():
    def __init__(self,max_symbols,max_params):
        self.dic = {}
        self.dic_params = {}
        self.dic_sym = {}
        count = 1
        for i in ["RANGESEP","MEMSEP1","MEMSEP2","MEMSEP3","SEP1","SEP2","MEMSEPIN","MEMSEPOUT","EMPTYMEMLET"]:
            self.dic[i] = count
            count += 1
        for i in [0,1,2,3,4,5,6,7,8,9]:
            self.dic[str(i)] = count
            count += 1
        self.ops = ["-","~","**","*","+",",","/",":","(",")","ceiling","floor","Mod","Min","Max","int_ceil","int_D"]
        for i in self.ops:
            self.dic[i] = count
            count += 1
        for i in range(max_symbols):
            self.dic_sym["N"+str(i)] = count
            count += 1
        for i in range(max_params):
            self.dic_params["i"+str(i)] = count
            count += 1
        self.len = count

    def shuffle_sym(self):
        l = list(self.dic_sym.items())
        random.shuffle(l)
        self.dic_sym = dict(self.dic_sym)

    def __len__(self):
        return self.len


    def encode(self,text):
        if text == "":
            return []
        if text[0:1] == " ":
            return self.encode(text[1:])
        for i in self.dic:
            if text.startswith(i):
                return [self.dic[i]]+self.encode(text[len(i):])
        for i in self.dic_params:
            if text.startswith(i):
                return [self.dic_params[i]]+self.encode(text[len(i):])
        for i in self.dic_sym:
            if text.startswith(i):
                return [self.dic_sym[i]]+self.encode(text[len(i):])


def gen_set(Vecto,encoder):
    X = []
    Y = []
    for vec in tqdm(Vecto):
        augmented_data_in_memlet = []
        augmented_data_map = []
        augmented_data_out_memlet = []
        augmented_data_Y = []
        encoder.shuffle_sym()
        for j in range(8):
            map_str = ""
            for i in reversed(vec["Map_entry"]):
                map_str += i[0]+"SEP1"+range2str(i[1])+"SEP2"
            #vec_str += "MEMIN"
            in_mem_str = ""
            for i in vec["In_Memlet"]:
                in_mem_str += mem2str(i)+"MEMSEPIN"
            #vec_str += "MEMOUT"
            out_mem_str = ""
            for i in vec["Out_Memlet"]:
                out_mem_str += mem2str(i)+"MEMSEPOUT"
            res = [encoder.encode(map_str),encoder.encode(in_mem_str),encoder.encode(out_mem_str)]
            augmented_data_map.append(np.array(res[0]))
            augmented_data_in_memlet.append(np.array(res[1]))
            augmented_data_out_memlet.append(np.array(res[2]))
            augmented_data_Y += [vec["Result"]]
        X+=[[torch.Tensor(np.array(augmented_data_map)).type(torch.LongTensor)\
            ,torch.Tensor(np.array(augmented_data_in_memlet)).type(torch.LongTensor)\
                ,torch.Tensor(np.array(augmented_data_out_memlet)).type(torch.LongTensor)]]
        Y+=[[augmented_data_Y]]
    return {"X":X,"Y":Y,"vocab_size":len(encoder)}

raw_data = {}
with open("/Users/benediktschesch/MyEnv/Vectorization_normalized_dic.pkl", "rb") as fp:    
    raw_data = symbolic.SympyAwareUnpickler(fp).load()
max_symbols = raw_data["max_symbols"]
max_params = raw_data["max_params"]
Vectorizations = raw_data["data"]
encoder = Encoder(max_symbols,max_params)
Vec_train, Vec_test = train_test_split(Vectorizations, test_size=0.2)
with open("/Users/benediktschesch/MyEnv/Vectorization_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(gen_set(Vectorizations,encoder))
with open("/Users/benediktschesch/MyEnv/Vectorization_train_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(gen_set(Vec_train,encoder))
with open("/Users/benediktschesch/MyEnv/Vectorization_test_data.pkl", "wb") as fp:
    symbolic.SympyAwarePickler(fp).dump(gen_set(Vec_test,encoder))