#
#This file takes the training/test data and trains our model defined in Vect_GNN.py
#
from os import terminal_size
import torch
import math
import networkx as nx
import torch.nn as nn
import numpy as np
import torch
from torch.utils.data import DataLoader
from torch import Tensor, optim
import pickle
from tqdm import tqdm
import pandas as pd
from GNN import GNN,Embedder
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import Encoder,map2str,mem2str



device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
with open("/Users/benediktschesch/MyEnv/temp/train_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


def predictions(loader,model):
    points = 0
    correct_points = 0
    for x in loader:
        #GPU Support
        for i in range(len(x["G"]["adjacency_lists"])):
            x["G"]["adjacency_lists"][i] = x["G"]["adjacency_lists"][i].to(device)
        for i in x["G"]["node_data"]:
            if "data" in i:
                i["data"] = i["data"].to(device)
            i["Type"]  = i["Type"].to(device)
        x["G"]["node_to_graph_idx"] = x["G"]["node_to_graph_idx"].to(device)
        for i in range(len(x["results"])):
            x["results"][i] = x["results"][i].to(device)
        for i in range(len(x["map_entry_idx"])):
            x["map_entry_idx"][i]  = x["map_entry_idx"][i].to(device)
        x["speedup"] = x["speedup"].to(device)
        #GPU Support
        
        graph = x["G"]
        for node in graph["node_data"]:
            if "data" in node:
                result = model(node)
                for index,i in enumerate(result):
                    points += 1
                    if torch.argmax(i) == node["data"][0][index]:
                        correct_points+= 1
    return correct_points*1.0/points

max_vocab = raw_data["dim_in"]
training_infos = []
X_train = raw_data["X_train"][:16]
X_test = raw_data["X_test"][:16]
max_num_param = raw_data["max_num_param"]
print("Device: ",device)
print("Number of training graphs: {}".format(len(X_train)))
print("Number of validation graphs: {}".format(len(X_test)))


trainloader = DataLoader(X_train,batch_size=1)
testloader = DataLoader(X_test,batch_size=1)

model = Embedder(vocab_size = max_vocab,dim_hidden = 128,embedding_dim = 128,num_layers = 1,\
    max_num_param = 1,size = 6)
model.to(device)
optimizer = optim.SGD(model.parameters(), lr=0.008)
criterion = nn.CrossEntropyLoss()
epochs = 2
print("Number of Parameters:",sum(p.numel() for p in model.parameters()))

def adjust_optim(optimizer, epoch):
    if epoch < 15:
        optimizer.param_groups[0]['lr'] = 0.005
    elif epoch < 25:
        optimizer.param_groups[0]['lr'] = 0.003
    elif epoch < 35:  
        optimizer.param_groups[0]['lr'] = 0.001
    elif epoch < 50:  
        optimizer.param_groups[0]['lr'] = 0.0005


epochs = 50
for e in range(epochs):
    running_loss = 0
    points = 0
    correct_points = 0
    for x in trainloader:
        #GPU Support
        for i in range(len(x["G"]["adjacency_lists"])):
          x["G"]["adjacency_lists"][i] = x["G"]["adjacency_lists"][i].to(device)
        for i in x["G"]["node_data"]:
          if "data" in i:
            i["data"] = i["data"].to(device)
          i["Type"]  = i["Type"].to(device)
        x["G"]["node_to_graph_idx"] = x["G"]["node_to_graph_idx"].to(device)
        for i in range(len(x["results"])):
            x["results"][i] = x["results"][i].to(device)
        for i in range(len(x["map_entry_idx"])):
            x["map_entry_idx"][i]  = x["map_entry_idx"][i].to(device)
        x["speedup"] = x["speedup"].to(device)
        #GPU Support
        
        graph = x["G"]
        for node in graph["node_data"]:
            if "data" in node:
                optimizer.zero_grad()
                result = model(node)
                loss = criterion(result,node["data"][0])
                if loss == 0 or math.isnan(loss.item()):
                    continue
                for index,i in enumerate(result):
                    points += 1
                    if torch.argmax(i) == node["data"][0][index]:
                        correct_points+= 1
                loss.backward()
                optimizer.step()
                running_loss += loss.item()
    train_accuracy = correct_points*1.0/points
    test_accuracy = predictions(testloader,model)
    print("Epoch: {}/{} Training loss: {} Training accuracy: {} Testing accuracy: {}"\
        .format(e+1,epochs,"{:.6f}".format(running_loss/points),\
            "{:.6f}".format(train_accuracy),"{:.6f}".format(test_accuracy)))
    training_infos.append([e,running_loss/points,train_accuracy])
    adjust_optim(optimizer,e)
train_accuracy = predictions(trainloader,model)
test_accuracy = predictions(testloader,model)
print("Training accuracy: ",train_accuracy,"Average Training Speedup: ")
print("Validation accuracy: ",test_accuracy,"Average Validation Speedup: ")
df = pd.DataFrame(training_infos,columns=["Epoch","Training Loss","Training Accuracy",\
    "Validation Accuracy","Average Training Speedup","Average Validation Speedup"],)
df.to_csv("/Users/benediktschesch/MyEnv/GNN_RL/training_infos.csv")
torch.save(model.state_dict(),"model_embedding_lstm.pt")
print("Model has been saved")