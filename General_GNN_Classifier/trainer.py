import random
from pathlib import Path
from typing_extensions import TypedDict
import torch
from docopt import docopt
from dpu_utils.utils import RichPath, run_and_debug
import math
import networkx as nx
import copy
import numpy as np
from sklearn.model_selection import train_test_split
import torch.nn as nn
import torch
from torch.utils.data import Dataset, DataLoader
from torch import Tensor, optim
import pickle
from tqdm import tqdm
import sys
sys.path.append("/Users/benediktschesch/MyEnv/Vectorization_GNN")
from Vect_GNN import GNN,create_graph2class_gnn_model

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
with open("/Users/benediktschesch/MyEnv/temp/Graph_train_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


max_vocab = raw_data["dim_in"]
X = raw_data["data"]
trans_map_entry = raw_data["transformations_map_entry"]
trans_tasklet = raw_data["transformations_tasklet"]

X_train,X_test = train_test_split(X, test_size=0.2)
print("Device: ",device)
print("Number of graphs: {}".format(len(X)))
print("Number of training graphs: {}".format(len(X_train)))
print("Number of validation graphs: {}".format(len(X_test)))
for i in raw_data["transformations_data_map"]:
    print("Transformation: ",i[0]," Number of Training Points: ",i[1]," Positive Rate: ",i[1]*100.0/i[2],"%")
for i in raw_data["transformations_data_task"]:
    print("Transformation: ",i[0]," Number of Training Points: ",i[1]," Positive Rate: ",i[1]*100.0/i[2],"%")


class my_dataset(Dataset):
    def __init__(self,data):
        self.data=data
    def __getitem__(self, index):
        return self.data[index]
    def __len__(self):
        return len(self.data)


def predictions(loader,model):
    correct_result = 0
    total = 0.0
    with torch.no_grad():
        for x in loader:
            graph = x["G"]
            tasklet,map_entry = model(graph,x["tasklet"],x["map_entry"])
            for i in range(len(x["list_trans_tasklet"])):
                for i in range(len(tasklet)):
                    total+=1
                    if torch.argmax(tasklet[i]) == x["list_trans_tasklet"][i]["results"][0]:
                        correct_result +=1
            for i in range(len(x["list_trans_map_entry"])):
                for i in range(len(tasklet)):
                    total+=1
                    if torch.argmax(map_entry[i]) == x["list_trans_map_entry"][i]["results"][0]:
                        correct_result +=1
    return 1.0*correct_result/(1.0*total)

datasettrain = my_dataset(X_train)
trainloader = DataLoader(X_train,batch_size=1)
datasettest = my_dataset(X_test)
testloader = DataLoader(X_test,batch_size=1)

model = GNN(dim_in = max_vocab,dim_hidden = 100,embedding_dim = 100,num_layers = 1,\
    transformations_tasklet = len(raw_data["transformations_tasklet"]),\
    transformations_map_entry = len(raw_data["transformations_map_entry"]))
model.compute_metada(DataLoader(X,batch_size=1))
optimizer = optim.SGD(model.parameters(), lr=0.0005)
criterion = nn.CrossEntropyLoss()
epochs = 50

def adjust_optim(optimizer, epoch):
    if epoch < 15:
        optimizer.param_groups[0]['lr'] = 0.0005
    elif epoch < 25:
        optimizer.param_groups[0]['lr'] = 0.0001
    elif epoch < 35:  
        optimizer.param_groups[0]['lr'] = 0.00003
    elif epoch < 50:  
        optimizer.param_groups[0]['lr'] = 0.00001


for e in range(epochs):
    running_loss = 0
    points = 0
    for x in trainloader:
        graph = x["G"]
        # setting gradient to zeros
        optimizer.zero_grad()
        tasklet,map_entry = model(graph,x["tasklet"],x["map_entry"])
        loss = 0
        for i in range(len(x["list_trans_tasklet"])):
            points += len(x["tasklet"])
            loss += criterion(tasklet[i],x["list_trans_tasklet"][i]["results"][0])
        for i in range(len(x["list_trans_map_entry"])):
            points += len(x["tasklet"])
            loss += criterion(map_entry[i],x["list_trans_map_entry"][i]["results"][0])

        # backward propagation
        loss.backward()
        # update the gradient to new gradients
        optimizer.step()
        if math.isnan(loss.item()):
            continue
        running_loss += loss.item()
        assert not math.isnan(running_loss)
    print("Epoch: {}/{} Training loss: {} Validation accuracy: {} Training accuracy: {}".format(e,(epochs-1),\
        "%.3f" % (running_loss/points),"%.3f" % predictions(testloader,model),\
        "%.3f" % predictions(trainloader,model)))
    #adjust_optim(optimizer,e)

print("Training accuracy:"+str(predictions(X_train,model)))
print("Validation accuracy:"+str(predictions(X_test,model)))