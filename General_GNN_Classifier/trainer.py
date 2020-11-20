#
#This file takes the training/test data and trains our model defined in Vect_GNN.py
#
import torch
import math
import networkx as nx
import torch.nn as nn
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
with open("/Users/benediktschesch/MyEnv/temp/Graph_train_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


max_vocab = raw_data["dim_in"]
trans_map_entry = raw_data["transformations_map_entry"]
trans_tasklet = raw_data["transformations_tasklet"]

X_train = raw_data["X_train"]
X_test = raw_data["X_test"]

print("Device: ",device)
print("Number of training graphs: {}".format(len(X_train)))
print("Number of validation graphs: {}".format(len(X_test)))
for i in raw_data["transformations_data_map"]:
    print("Transformation: ",i[0]," Number of Training Points: ",i[2]," Positive Rate: ",i[1]*100.0/i[2],"%")
for i in raw_data["transformations_data_task"]:
    print("Transformation: ",i[0]," Number of Training Points: ",i[2]," Positive Rate: ",i[1]*100.0/i[2],"%")




def predictions(loader,model,trans_map_entry,trans_tasklet):
    stats = [[0,0] for i in trans_tasklet]
    stats1 = [[0,0] for i in trans_map_entry]
    with torch.no_grad():
        for x in loader:
            graph = x["G"]
            tasklet,map_entry = model(graph,x["tasklet"],x["map_entry"])
            correct_result = 0
            total = 0.0
            for i in range(len(x["list_trans_tasklet"])):
                for j in range(len(tasklet[0])):
                    stats[i][0] += 1
                    if torch.argmax(tasklet[0][j]) == x["list_trans_tasklet"][i]["results"][0][j]:
                        stats[i][1] += 1
            for i in range(len(x["list_trans_map_entry"])):
                correct_result = 0
                total = 0.0
                for j in range(len(map_entry[0])):
                    stats1[i][0] +=1
                    if torch.argmax(map_entry[0][j]) == x["list_trans_map_entry"][i]["results"][0][j]:
                        stats1[i][1] +=1

    for i in range(len(stats)):
        print("Transformation: ",trans_tasklet[i].__name__," Accuracy:",\
                        "{:.3f}".format(stats[i][1]/stats[i][0]))
    for i in range(len(stats1)):
        print("Transformation: ",trans_map_entry[i].__name__," Accuracy:",\
                        "{:.3f}".format(stats1[i][1]/stats1[i][0]))

trainloader = DataLoader(X_train,batch_size=1)
testloader = DataLoader(X_test,batch_size=1)

model = GNN(dim_in = max_vocab,dim_hidden = 200,embedding_dim = 200,num_layers = 2,\
    transformations_tasklet = len(raw_data["transformations_tasklet"]),\
    transformations_map_entry = len(raw_data["transformations_map_entry"]))
model.compute_metada(trainloader)
optimizer = optim.Adam(model.parameters(), lr=0.00008)
criterion = nn.CrossEntropyLoss()
epochs = 50

def adjust_optim(optimizer, epoch):
    if epoch < 15:
        optimizer.param_groups[0]['lr'] = 0.00008
    elif epoch < 25:
        optimizer.param_groups[0]['lr'] = 0.00003
    elif epoch < 35:  
        optimizer.param_groups[0]['lr'] = 0.00001
    elif epoch < 50:  
        optimizer.param_groups[0]['lr'] = 0.000005


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
            points += x["tasklet"].nelement()
            loss += criterion(tasklet[i],x["list_trans_tasklet"][i]["results"][0])
        for i in range(len(x["list_trans_map_entry"])):
            points += x["map_entry"].nelement()
            loss += criterion(map_entry[i],x["list_trans_map_entry"][i]["results"][0])

        if math.isnan(loss.item()):
            continue
        loss.backward()
        optimizer.step()
        running_loss += loss.item()
        assert not math.isnan(running_loss)
    print("Epoch: {}/{} Training loss: {}".format(e+1,epochs,"{:.4f}".format(running_loss/points)))
    if e % 4 == 0:
        print("====================================================")
        print("Test set:")
        predictions(testloader,model,trans_map_entry,trans_tasklet)
        print("Training set:")
        predictions(trainloader,model,trans_map_entry,trans_tasklet)
        print("====================================================")
    adjust_optim(optimizer,e)
print("Training accuracy:")
predictions(trainloader,model,trans_map_entry,trans_tasklet)
print("Validation accuracy:")
predictions(testloader,model,trans_map_entry,trans_tasklet)