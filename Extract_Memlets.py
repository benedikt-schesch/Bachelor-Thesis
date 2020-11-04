import dace
import numpy as np
import os
import tensorflow as tf
from tensorflow import keras
from sklearn.model_selection import train_test_split
import random
from LSTM import LSTM_Encoder
from LSTM import Network
import re
import torch.nn as nn
import torch
from torch.utils.data import TensorDataset, DataLoader, Dataset
from torch import optim
import pickle

class Converter:
    def __init__(self):
        self.current = 70
        self.dic = dict()

    def convert(self,string):
        if string in self.dic:
            return self.dic[string]
        else:
            self.dic[string] = chr(self.current)
            self.current += 1
            return self.dic[string]
    def __len__(self):
        return len(self.dic)+5

X = []
Y = []
Memlets = []
count = 0
directory = "/Users/benediktschesch/MyEnv/tests/.dacecache"
num_positive = 0
for filename in os.listdir(directory):
    print(filename)
    if filename in [".DS_Store","tile_twice_test"]:
        continue
    sdfg = dace.SDFG.from_file(os.path.join(os.path.join(directory, filename),"program.sdfg"))
    conv = Converter()
    for State in sdfg.nodes():
        for Memlet in State.edges():
            if hasattr(Memlet.data.subset, 'ranges'):
                dictionary = {}
                dict_free_symbol = {}
                dic = {}
                for free_symbol in Memlet.data.free_symbols:
                    dict_free_symbol[dace.symbol(free_symbol)] = dace.symbol(conv.convert(free_symbol))
                    dic[dace.symbol(free_symbol)] = dace.symbol("N")
                #print(Memlet.data.subset[0])
                dictionary["Volume"] = str(Memlet.data.volume.subs(dict_free_symbol))
                dictionary["Dynamic"] = Memlet.data.dynamic
                num_range = 0
                test = True
                test2 = True
                max_range = len(Memlet.data.subset.ranges)-1
                #print(Memlet.data.subset.ranges)
                for rge in Memlet.data.subset.ranges:
                    info = []
                    for r in rge:
                        info.append(str(r.subs(dict_free_symbol)))
                    dictionary["Range"+str(num_range)] = info
                    # Check if ND access is one-dimensional-contiguous
                    # definition: subset can be seen as a one dimensional set of elements in the contiguous dimension
                    # more than one dimension is not allowed no matter what
                    # Example:
                    # A[0:N, 5] - not OK
                    # A[5, 0:N] - OK
                    # A[0:N, 5:N] - not OK
                    # A[0,1,2,3,4, i:i+5] - OK

                    #Test1 covers the case where there is more than 1 row
                    if num_range == max_range and str(rge[1].subs(dic)) != "N - 1":
                        test = False
                    if num_range == max_range and (info[0] != "0"  or info[2] != "1"):
                        test = False
                    elif num_range < max_range and str(rge[2]) != "1":
                        test = False

                    #Test2 checks for the special case where everything is on 1 row
                    if num_range == max_range and str(rge[2]) != "1": 
                        test2 = False
                    elif num_range < max_range and str(rge[1]) != str(rge[0]):
                        test2 = False
                    num_range+=1
                if max_range == 0 and str(Memlet.data.subset.ranges[0][2]) == "1":
                    test = True
                dictionary["Result"] = test or test2
                Memlets.append(dictionary)
    count = max(count,len(conv))
class Encoder():
    def __init__(self,length):
        self.dic = {}
        for i in [0,1,2,3,4,5,6,7,8,9]:
            self.dic[str(i)] = i
        self.dic["-"] = 10
        self.dic["+"] = 11
        self.dic["/"] = 12
        self.dic["*"] = 13
        self.dic[":"] = 14
        self.dic["("] = 15
        self.dic[")"] = 16
        count = 17
        for i in range(65,65+length):
            self.dic[chr(i)] = count
            count+=1
        self.len = count
    
    def encode(self,encode):
        #result = [0 for i in range(self.len)]
        #for i in encode:
            #result[self.dic[i]] = 1
        return self.dic[encode]


encoder = Encoder(count)

for Memlet in Memlets:
    text = Memlet["Volume"]+"A"
    if Memlet["Dynamic"]:
        text+= "B"+"A"
    else:
        text+= "C"+"A"
    index = 0
    while ("Range"+str(index)) in Memlet:
        rge = Memlet[("Range"+str(index))]
        text+=rge[0]+":"+rge[1]+":"+rge[2]+"A"
        index+=1
    text = text.replace(' ','')
    text = text.replace('floor', 'D')
    text = text.replace('ceiling', 'E')
    if "int_ceil" not in text and "Mod" not in text and "Min" not in text and "Max" not in text and "int_D" not in text:
        result = []
        for element in text:
            result.append(encoder.encode(element))
        X.append([np.array(result),int(Memlet["Result"])])
        if Memlet["Result"]:
            num_positive += 1

print("Positive rate: {}%".format(num_positive*100.0/len(X)))

with open("/Users/benediktschesch/MyEnv/Memlets_data.txt", "wb") as fp:
    pickle.dump(X, fp)
