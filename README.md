# Bachelor-Thesis
My Bachelor Thesis Github repo \
This is a work in progres and should not be used for now. \
It is assumed that you are already somewhat familiar with DaCe. \
To learn more about DaCe: \
https://github.com/spcl/dace \
https://www.youtube.com/watch?v=ujKZXUmFAlw&feature=youtu.be&ab_channel=SPCLLab \
https://arxiv.org/abs/1902.10345 

What are the different folders? 

-Reachability: Uses GNN to solve the Reachability Problem in a graph \
-Vectorization_NN: Takes the Memlet and Map Entry and predicts if it's vectorizable \
-Vectorization_GNN: Embeds all states of the SDFG in a graph and then uses a GNN to predict if we can apply the vectorization transformation \
-General_GNN_clasifier:Embeds all states of the SDFG in a graph and then uses a GNN to predict if we can apply any transformation in DaCe 
