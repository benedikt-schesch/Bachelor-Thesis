import numpy as np
import os
from numpy.lib.function_base import append
import tensorflow as tf
from tensorflow import keras
from sklearn.model_selection import train_test_split
import random
from LSTM import LSTM_Encoder
from LSTM import Network
import re
import torch.nn as nn
import torch
from torch.utils.data import Dataset, DataLoader
from torch import Tensor, optim
import pickle
from tqdm import tqdm
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
if torch.cuda.is_available():
  torch.set_default_tensor_type('torch.cuda.FloatTensor')
else:
  torch.set_default_tensor_type('torch.FloatTensor')
with open("/Users/benediktschesch/MyEnv/Vectorization_train_data.pkl", "rb") as fp:   # Unpickling
    raw_train_data = pickle.load(fp)
with open("/Users/benediktschesch/MyEnv/Vectorization_test_data.pkl", "rb") as fp:   # Unpickling
    raw_test_data = pickle.load(fp)
with open("/Users/benediktschesch/MyEnv/Vectorization_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)
max_vocab = raw_data["vocab_size"]
X,X_test,Y,y_test = train_test_split(raw_data["X"],raw_data["Y"], test_size=0.2)
#X,Y = raw_train_data["X"], raw_train_data["Y"]
#X_test,y_test = raw_test_data["X"], raw_test_data["Y"]
zeros = 0
for val in Y:
    if val[0][0] == 0:
        zeros+=1
print("Device: ",device)
print("Positive rate: {}%".format(zeros*100.0/len(Y)))
print("Number of training points: {}".format(len(Y)))
print("Number of validation points: {}".format(len(y_test)))
print("Data augmentation factor: {}".format(len(X[0][0])))

tensor_y = torch.Tensor(Y)
tensor_y_test = torch.Tensor(y_test)
tensor_y = tensor_y.type(torch.LongTensor)

class my_dataset(Dataset):
    def __init__(self,data,label):
        self.data=data
        self.label=label          
    def __getitem__(self, index):
        return self.data[index],self.label[index]
    def __len__(self):
        return len(self.data)

def predictions(loader,model):
    correct_result = 0
    with torch.no_grad():
      for X,correct in loader:
        x = X[0]
        y = X[1]
        z = X[2]
        x, y,z,correct = x.to(device), y.to(device),z.to(device),correct.to(device)
        output = model(x,y,z)
        for i in range(len(X[0])):
            if torch.argmax(output[i]) == correct[0][0][i]:
                correct_result +=1
    return 1.0*correct_result/(len(loader)*len(X[0]))

dataset = my_dataset(X,tensor_y) # create your datset
trainloader = DataLoader(dataset,batch_size=1) # create your dataloader
datasettest = my_dataset(X_test,tensor_y_test) # create your datset
testloader = DataLoader(datasettest) # create your dataloader

model = Network(dim_in = (max_vocab+1),dim_hidden = 100,embedding_dim = 100,num_layers = 2)
optimizer = optim.SGD(model.parameters(), lr=0.1)
criterion = nn.CrossEntropyLoss()
epochs = 1

def adjust_optim(optimizer, epoch):
    if epoch < 5:
        optimizer.param_groups[0]['lr'] = 0.2
    elif epoch < 20:
        optimizer.param_groups[0]['lr'] = 0.1
    elif epoch < 40:  
        optimizer.param_groups[0]['lr'] = 0.05
    elif epoch < 50:  
        optimizer.param_groups[0]['lr'] = 0.01

for e in range(epochs):
    running_loss = 0
    for X,correct in tqdm(trainloader):
        x = X[0]
        y = X[1]
        z = X[2]
        x, y,z,correct = x.to(device), y.to(device),z.to(device),correct.to(device)
        # setting gradient to zeros
        optimizer.zero_grad()        
        output = model(x,y,z)
        loss = criterion(output, correct[0][0])
        # backward propagation
        loss.backward()
        # update the gradient to new gradients
        optimizer.step()
        running_loss += loss.item()
    
    adjust_optim(optimizer,e)
    print("Epoch: {}/{} Training loss: {} Validation accuracy: {}".format(e,(epochs-1),"%.3f" % (running_loss/len(trainloader)),"%.3f" % predictions(testloader,model)))

print("Training accuracy:"+str(predictions(testloader,model)))
print("Validation accuracy:"+str(predictions(trainloader,model)))




# def random_array():
#     arr = [1]
#     for i in range(30+3*count):
#         arr.append(random.randint(0, 1))
#     if sum(arr) == 1 and arr[2+20+2*len(conv)] == 1:
#         return random_array()
#     else:
#         return arr

# X = np.array([np.zeros(101)])
# y = np.array([[0]])

# for Memlet in Memlets:
#     Volume_array = encoder.encode(Memlet["Volume"])
#     Dynamic_array = np.array([int(Memlet["Dynamic"])])
#     Range0_array = np.array([1])
#     test = Memlet["Range0"][2] == "1"
#     for rge in Memlet["Range0"]:
#         Range0_array = np.append(Range0_array,encoder.encode(rge))
#     Range1_array = np.array([])
#     if "Range1" in Memlet:
#         test = test and (Memlet["Range1"][2] == "1")
#         Range1_array = np.append(Range1_array,np.array([1]))
#         for rge in Memlet["Range1"]:
#             Range1_array = np.append(Range1_array,encoder.encode(rge))
#     else:
#         Range1_array = np.append(Range1_array,np.array([0]))
#         for rge in ["","",""]:
#             Range1_array = np.append(Range1_array,encoder.encode(rge))
#     Memlet_array = np.concatenate((Volume_array,Dynamic_array,Range0_array,Range1_array))
#     X = np.append(X,np.array([Memlet_array]),axis = 0)
#     y = np.append(y,np.array([[int(test)]]),axis = 0)
#     Not_Memlet_array1 = np.concatenate((Volume_array,Dynamic_array,random_array(),Range1_array))
#     X = np.append(X,np.array([Not_Memlet_array1]),axis = 0)
#     y = np.append(y,np.array([[0]]),axis = 0)





# in_features = len(X[0])
# X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# model = keras.Sequential([
#     keras.layers.Dense(in_features, activation='relu'),
#     keras.layers.Dense(50,activation='relu'),
#     keras.layers.Dense(1),
# ])

# model.compile(optimizer='adam',
#               loss='binary_crossentropy',
#               metrics=['accuracy'])

# model.fit(X_train, y_train, epochs=100)

# test_loss, test_acc = model.evaluate(X_test,y_test, verbose=2)

# print('\nTest accuracy:', test_acc)