import os
import torch
import math
import networkx as nx
import torch.nn as nn
from sklearn.model_selection import train_test_split
import numpy as np
import torch
from torch.utils.data import DataLoader
from torch import Tensor, optim
import pickle
from tqdm import tqdm
import pandas as pd
from GNN import GNN
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import Encoder,map2str,mem2str

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
with open("GNN_RL2/metadata.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)

batch_size = 32
path = "GNN_RL2/dataset"
paths = []
for root, dirs, files in os.walk(path):
    for file in files:
        paths.append(os.path.join(root, file))

max_vocab = raw_data["dim_in"]
training_infos = []
X_train, X_test = train_test_split(paths, test_size=0.2)
max_num_param = raw_data["max_num_param"]
print("Device: ",device)
print("Number of data points: {}".format(len(paths)))
print("Number of training points: {}".format(len(X_train)))
print("Number of validation points: {}".format(len(X_test)))
print("Average Speedup: ",raw_data["Average Speedup"])


def predictions(loader,model):
    num_elem = 0
    correct = 0
    speedup = 0
    missclasified = set()
    with torch.no_grad():
        for paths in loader:
                for path in paths:
                    x = pickle.load(open(path, "rb"))
                    #GPU Support
                    for i in range(len(x["G"]["adjacency_lists"])):
                        x["G"]["adjacency_lists"][i] = x["G"]["adjacency_lists"][i].to(device)
                    for i in x["G"]["node_data"]:
                        if "data" in i:
                            i["data"] = i["data"].to(device)
                        i["Type"]  = i["Type"].to(device)
                    x["G"]["node_to_graph_idx"] = x["G"]["node_to_graph_idx"].to(device)
                    #GPU Support
                    
                    graph = x["G"]
                    result = model(graph,x["map_entry_idx"])
                    num_elem += 1
                    if torch.argmax(result).item() == (x["results"][0]):
                        correct += 1
                    else:
                        missclasified.add((x["file"],x["map_entry"]["data"]))
                    speedup += x["speedup_dic"][torch.argmax(result).item()]
    return correct*1.0/num_elem,speedup/num_elem,missclasified

trainloader = DataLoader(X_train,batch_size=batch_size)
testloader = DataLoader(X_test,batch_size=batch_size)
data_metadata = pickle.load(open(paths[0], "rb"))

device = torch.device('cpu')
torch.set_default_tensor_type('torch.FloatTensor')
model = GNN(vocab_size = max_vocab,dim_hidden = 150,embedding_dim = max_vocab,num_layers = 1,\
    max_num_param = 1,size = 6)
model.compute_metada([data_metadata],device)
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
model.to(device)
model.todevice(device)
optimizer = optim.SGD(model.parameters(), lr=0.008)
criterion = nn.CrossEntropyLoss()
epochs = 1
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
    correct_points = 0
    speedup = 0
    for paths in trainloader:
        optimizer.zero_grad()
        predict = []
        result = []
        for path in paths:
            x = pickle.load(open(path, "rb"))
            #GPU Support
            for i in range(len(x["G"]["adjacency_lists"])):
                x["G"]["adjacency_lists"][i] = x["G"]["adjacency_lists"][i].to(device)
            for i in x["G"]["node_data"]:
                if "data" in i:
                    i["data"] = i["data"].to(device)
                i["Type"]  = i["Type"].to(device)
            x["G"]["node_to_graph_idx"] = x["G"]["node_to_graph_idx"].to(device)
            #GPU Support
            
            graph = x["G"]
            res = model(graph,x["map_entry_idx"])
            points += 1
            if torch.argmax(res).item() == (x["results"][0]):
                correct_points += 1
            speedup += x["speedup_dic"][torch.argmax(res).item()]
            result.append(x["results"][0])
            predict.append(res)
        loss = criterion(torch.stack(predict),torch.tensor(result))
        if loss == 0 or math.isnan(loss.item()):
            continue
        loss.backward()
        optimizer.step()
        running_loss += loss.item()
    train_accuracy = correct_points*1.0/points
    test_accuracy,test_speedup,_ = predictions(testloader,model)
    train_speedup = speedup/points
    print("Epoch: {}/{} Training loss: {} Training accuracy: {} Test accuracy: {} Average Training Speedup: {} Average Testing Speedup: {}"\
        .format(e+1,epochs,"{:.6f}".format(running_loss/points),\
            "{:.6f}".format(train_accuracy),"{:.6f}".format(test_accuracy),\
            "{:.6f}".format(train_speedup),"{:.6f}".format(test_speedup)))
    training_infos.append([e,running_loss/points,train_accuracy,test_accuracy,train_speedup,test_speedup])
    adjust_optim(optimizer,e)
train_accuracy, train_speedup,miss_train = predictions(trainloader,model)
test_accuracy, test_speedup,miss_test = predictions(testloader,model)
print("Training accuracy: ",train_accuracy,"Average Training Speedup: ",train_speedup)
print("Validation accuracy: ",test_accuracy,"Average Validation Speedup: ",test_speedup)
df = pd.DataFrame(training_infos,columns=["Epoch","Training Loss","Training Accuracy",\
    "Validation Accuracy","Average Training Speedup","Average Validation Speedup"],)
df.to_csv("/Users/benediktschesch/MyEnv/GNN_RL/training_infos.csv")
torch.save(model.state_dict(),"model.pt")
print("Model has been saved")


# model2 = GNN(vocab_size = max_vocab,dim_hidden = 128,embedding_dim = 128,num_layers = 2,\
#     max_num_param = 1,size = 6)
# model2.compute_metada(testloader,device)
# model2.load_state_dict(torch.load("model.pt"))

# from torch.utils.tensorboard import SummaryWriter
# import tensorflow as tf
# import tensorboard as tb
# tf.io.gfile = tb.compat.tensorflow_stub.io.gfile
# writer = SummaryWriter('runs/embedding')
# encoder = raw_data["encoder"]
# labels = [i[0] for i in encoder.maping()]
# embeddings = model.word_embeddings(torch.Tensor([i[1] for i in encoder.maping()]).type(torch.LongTensor))
# writer.add_embedding(embeddings,
#                     metadata=labels)
# writer.close()
