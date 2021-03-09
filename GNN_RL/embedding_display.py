from GNN import Embedder
import pickle
import tensorboard
import torch
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter
import tensorflow as tf
import tensorboard as tb
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import Encoder,map2str,mem2str


with open("/Users/benediktschesch/MyEnv/temp/train_data.pkl", "rb") as fp:   # Unpickling
    raw_data = pickle.load(fp)


max_vocab = raw_data["dim_in"]
training_infos = []
X_train = raw_data["X_train"][:16]
X_test = raw_data["X_test"][:16]
max_num_param = raw_data["max_num_param"]
trainloader = DataLoader(X_train,batch_size=1)
testloader = DataLoader(X_test,batch_size=1)
model = Embedder(vocab_size = max_vocab,dim_hidden = 256,embedding_dim = 256,num_layers = 1,\
    max_num_param = 1,size = 6)
model.load_state_dict(torch.load("/Users/benediktschesch/MyEnv/GNN_RL/model_embedding_lstm.pt",map_location=torch.device('cpu')), strict=False)
#Compute memlet and map embeddings
memlet_embedding = []
map_embedding = []
for graph in trainloader:
  for x in graph["G"]["node_data"]:
    if x["Type"][0][0] == 1:
      map_embedding.append(model.map_embedding(x))
    if x["Type"][0][5] == 1:
      memlet_embedding.append(model.mem_embedding(x))
tf.io.gfile = tb.compat.tensorflow_stub.io.gfile
writer = SummaryWriter()
writer.add_embedding(torch.cat(memlet_embedding),tag = "Memlet")
writer.add_embedding(torch.cat(map_embedding),tag = "Map")
writer.close()
