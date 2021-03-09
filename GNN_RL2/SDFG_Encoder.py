import os
import pickle
import dace
from dace.sdfg.graph import MultiConnectorEdge
from dace.sdfg.nodes import AccessNode, MapEntry, MapExit, NestedSDFG, Tasklet, ConsumeEntry,ConsumeExit
from dace.sdfg import has_dynamic_map_inputs
import sys
sys.path.append("/Users/benediktschesch/MyEnv")
from utils import extract_map,extract_memlet,memlet2dic,map2dic,mem2str,map2str

def state_encoder(state):
    free_symbols = set({})
    params = set({})
    nodes_str = []
    map_entry = []
    tasklet = []
    count = 0
    dic_node = {}
    adj_lists = [[],[],[],[],[],[],[]]
    str_params_dic = {}
    freesymbol_dic = {}
    num_map_entry = 0
    list_nodes = []
    max_num_param = 0
    type_dic = {}
    type_dic[MultiConnectorEdge] = 1
    type_dic[AccessNode] = 2
    type_dic[MapEntry] = 3
    type_dic[MapExit] = 4
    type_dic[Tasklet] = 4
    type_dic[NestedSDFG] = 5

    for node in state.nodes():
        free_symbols.update(node.free_symbols)
        dic_node[node] = count
        adj_lists[0] += [(count,count)]
        if isinstance(node,MapEntry):
            params.update(node.params)
            for i,param in enumerate(reversed(node.params)):
                str_params_dic[param] = "i"+str(num_map_entry)+str(i)
                freesymbol_dic[dace.symbol(param)] = "i"+str(num_map_entry)+str(i)
            max_num_param = max(max_num_param,len(node.params))
            num_map_entry += 1
            ex = state.exit_node(node)
            if ex in dic_node:
                adj_lists[type_dic[MapExit]] += [(dic_node[ex],count)]
                adj_lists[type_dic[MapEntry]] += [(count,dic_node[ex])]
        if isinstance(node,MapExit):
            entry = state.entry_node(node)
            if entry in dic_node:
                adj_lists[type_dic[MapEntry]] += [(dic_node[entry],count)]
                adj_lists[type_dic[MapExit]] += [(count,dic_node[entry])]
        count += 1
        list_nodes += [node]

    for edge in state.edges():
        free_symbols.update(edge.data.free_symbols)
        u = edge._src
        v = edge._dst
        adj_lists[0] += [(count,count)]
        dic_node[edge] = count
        if type(u) not in type_dic or type(v) not in type_dic:
            raise Exception('Not Valid SDFG: Invalid type of nodes')
        for (a,b) in [(u,v),(v,u),(u,edge),(v,edge),(edge,u),(edge,v)]:
            if (dic_node[a],dic_node[b]) not in adj_lists[type_dic[type(edge._src)]]:
                adj_lists[type_dic[type(edge._src)]].append((dic_node[a],dic_node[b]))
        list_nodes += [edge]
        count += 1

    #Create free symbol dictionary
    for counter,sym in enumerate(list(free_symbols.difference(params))):
        freesymbol_dic[dace.symbol(sym)] = "N"+str(counter)

    for node in list_nodes:
        if isinstance(node,MapEntry):
            map_entry.append(dic_node[node])
            if has_dynamic_map_inputs(state,node):
                raise Exception('Not Valid SDFG: Dynamic map inputs')
            nodes_str.append({"Type":"MapEntry","data":map2str(map2dic(extract_map(node),freesymbol_dic,str_params_dic))})
        elif isinstance(node,Tasklet):
            tasklet.append(dic_node[node])
            nodes_str.append({"Type":type(node).__name__})
        elif isinstance(node,MultiConnectorEdge):
            nodes_str.append({"Type":"Memlet","data":mem2str(memlet2dic(extract_memlet(node),freesymbol_dic))})
        elif isinstance(node,(MapExit,NestedSDFG,AccessNode)):
            nodes_str.append({"Type":type(node).__name__})
        elif isinstance(node,ConsumeEntry) or isinstance(node,ConsumeExit):
            raise Exception('Not Valid SDFG: Invalid type of nodes')
        else:
            raise Exception('Not Valid SDFG: Invalid type of nodes')
    
    data_point = {"adjacency_lists":adj_lists,"node_data":nodes_str}
    num_free_symbols = len(free_symbols.difference(params))
    return data_point, max_num_param, num_map_entry, num_free_symbols

path = "GNN_RL2/SDFGS"
paths = []
for root, dirs, files in os.walk(path):
    for file in files:
        if file.endswith("_info.pkl"):
            paths.append(os.path.join(root, file)[:-9])


for id,path in enumerate(paths):
    print(id,"/",len(paths))ls
    
    measurements = pickle.load(open(path+"_info.pkl", "rb"))
    for mes in measurements:
        state_id = mes[1]
        map_entry_idx = mes[2]
        sdfg = dace.SDFG.from_file(path+".sdfg")
        if sdfg.sdfg_id != mes[0]:
            continue
        state = sdfg.node(state_id)
        try:
            data_point, max_num_param, num_map_entry, num_free_symbols = state_encoder(state)
        except Exception:
            continue
        data = {"G":data_point,"file": path,"timings": measurements[mes],"map_entry_idx":map_entry_idx,\
            "max_num_param":max_num_param,"num_map_entry":num_map_entry,"num_free_symbols":num_free_symbols}
        with open("GNN_RL2/ENC_SDFGS/data_"+str(id)+".pkl", "wb") as fp:
            pickle.dump(data,fp)