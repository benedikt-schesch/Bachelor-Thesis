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
with open("/Users/benediktschesch/MyEnv/temp/train_data_tot.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


max_vocab = raw_data["dim_in"]
transforms = raw_data["transforms"]
training_infos = [[],[],[],[]]
X_train = raw_data["X_train"]
X_test = raw_data["X_test"]

#In case one wants to have a single edge class
# for x in X_train:
#   for i in range(len(x["G"]["adjacency_lists"])-1):
#     x["G"]["adjacency_lists"][0] = torch.cat((x["G"]["adjacency_lists"][0],x["G"]["adjacency_lists"][i+1]),1)
#   x["G"]["adjacency_lists"] = [x["G"]["adjacency_lists"][0]]

# for x in X_test:
#   for i in range(len(x["G"]["adjacency_lists"])-1):
#     x["G"]["adjacency_lists"][0] = torch.cat((x["G"]["adjacency_lists"][0],x["G"]["adjacency_lists"][i+1]),1)
#   x["G"]["adjacency_lists"] = [x["G"]["adjacency_lists"][0]]
#In case one wants to have a single edge class

print("Device: ",device)
print("Number of training graphs: {}".format(len(X_train)))
print("Number of validation graphs: {}".format(len(X_test)))
for i in raw_data["transformations_data"]:
    print("Transformation: ",i[0]," Number of Training Points: ",i[2]," Positive Rate: ",i[1]*100.0/i[2],"%")



def predictions(loader,model,transforms,list):
    stats = [[0,0] for i in transforms]
    stat = []
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
                x["points"][i]  = x["points"][i].to(device)
            #GPU support

            graph = x["G"]
            res = model(graph,x["points"])
            for i in range(len(transforms)):
                for j in range(len(res[i])):
                    stats[i][0] += 1
                    if torch.argmax(res[i][j]) == x["results"][i][0][j]:
                        stats[i][1] += 1
    for i in range(len(stats)):
        stat.append(stats[i][1]/stats[i][0])
        print("Transformation: ",transforms[i][0].__name__," Accuracy:",\
                        "{:.4f}".format(stats[i][1]/stats[i][0]))
    list.append(stat)

trainloader = DataLoader(X_train,batch_size=1)
testloader = DataLoader(X_test,batch_size=1)

model = GNN(vocab_size = max_vocab,dim_hidden = 100,embedding_dim = max_vocab,num_layers = 3,\
    transforms = [len(i) for (_,i) in raw_data["transforms"]])
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
            x["points"][i]  = x["points"][i].to(device)
        #GPU Support
        
        graph = x["G"]
        # setting gradient to zeros
        optimizer.zero_grad()
        res = model(graph,x["points"])
        loss = 0
        for i in range(len(transforms)):
            points += x["results"][i][0].nelement()
            if res[i].nelement() == 0:
                continue
            loss += criterion(res[i],x["results"][i][0])
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
        predictions(testloader,model,transforms,training_infos[2])
        print("Training set:")
        predictions(trainloader,model,transforms,training_infos[3])
        print("====================================================")
    adjust_optim(optimizer,e)
print("Training accuracy:")
predictions(trainloader,model,transforms,[])
print("Validation accuracy:")
predictions(testloader,model,transforms,[])
np.savetxt("/Users/benediktschesch/MyEnv/temp/training_infos.csv", np.array(training_infos), delimiter=',')
torch.save(model.state_dict(),"model.pt")
print("Model has been saved")