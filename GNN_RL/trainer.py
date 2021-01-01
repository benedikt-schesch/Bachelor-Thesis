#
#This file takes the training/test data and trains our model defined in Vect_GNN.py
#
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
import sys
sys.path.append("/Users/benediktschesch/MyEnv/Vectorization_GNN")
from Vect_GNN import GNN

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
with open("/Users/benediktschesch/MyEnv/temp/train_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


max_vocab = raw_data["dim_in"]
training_infos = [[],[]]
X_train = raw_data["X_train"]
X_test = raw_data["X_test"]
max_num_param = raw_data["max_num_param"]
print("Device: ",device)
print("Number of training graphs: {}".format(len(X_train)))
print("Number of validation graphs: {}".format(len(X_test)))


def predictions(loader,model):
    num_elem = 0
    correct = 0
    with torch.no_grad():
        for x in loader:
            #GPU support
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
                x["map_entry_nparam"][i]  = x["map_entry_nparam"][i].to(device)
            #GPU support
            
            graph = x["G"]
            result = model(graph,x["map_entry_idx"],x["map_entry_nparam"])
            for j,res in enumerate(result):
                for i,elem in enumerate(res):
                    num_elem += 1
                    if torch.argmax(elem) == x["results"][j][0][i]:
                        correct += 1
    print(correct/num_elem)

trainloader = DataLoader(X_train,batch_size=1)
testloader = DataLoader(X_test,batch_size=1)

model = GNN(vocab_size = max_vocab,dim_hidden = 100,size = 6,embedding_dim = max_vocab,num_layers = 3,\
    max_num_param = max_num_param)
model.to(device)
model.compute_metada(trainloader,device)
optimizer = optim.SGD(model.parameters(), lr=0.008)
criterion = nn.CrossEntropyLoss()
epochs = 50
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

for e in range(epochs):
    running_loss = 0
    points = 0
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
            x["map_entry_nparam"][i]  = x["map_entry_nparam"][i].to(device)
        #GPU Support
        
        graph = x["G"]
        # setting gradient to zeros
        optimizer.zero_grad()
        #result = model(graph,x["map_entry_idx"],x["map_entry_nparam"])
        result = model(graph,x["map_entry_idx"],[torch.tensor([1]) for i in x["map_entry_nparam"]])
        loss = 0
        for j,res in enumerate(result):
            points += len(res)
            loss += criterion(res,x["results"][j][0][0].view(-1).type(torch.LongTensor))
        if loss == 0 or math.isnan(loss.item()):
            continue
        loss.backward()
        optimizer.step()
        running_loss += loss.item()
    print("Epoch: {}/{} Training loss: {}".format(e+1,epochs,"{:.6f}".format(running_loss/points)))
    if e % 9 == 0:
        print("====================================================")
        training_infos[0].append(e)
        training_infos[1].append(running_loss/points)
        print("Test set:")
        predictions(testloader,model)
        print("Training set:")
        predictions(trainloader,model)
        print("====================================================")
    adjust_optim(optimizer,e)
print("Training accuracy:")
predictions(trainloader,model)
print("Validation accuracy:")
predictions(testloader,model)
np.savetxt("/Users/benediktschesch/MyEnv/temp/training_infos.csv", np.array(training_infos), delimiter=',')
torch.save(model.state_dict(),"model.pt")
print("Model has been saved")