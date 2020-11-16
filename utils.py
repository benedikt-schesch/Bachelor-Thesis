import dace
import random
from dace.frontend.operations import detect_reduction_type
def range2list(range,dic_free_symbols):
    text = []
    for rge in range:
        text += [rge.subs(dic_free_symbols)]
    return text

def memlet2dic(memlet,dic_free_symbols):
    result = {}
    result["Dynamic"] = memlet["Dynamic"]
    result["Volume"] = memlet["Volume"].subs(dic_free_symbols)
    result["empty"] = memlet["empty"]
    count = 0
    while "Range"+str(count) in memlet:
        result["Range"+str(count)] = range2list(memlet["Range"+str(count)],dic_free_symbols)
        count += 1
    return result

def map2dic(map,dic_free_symbols,str_dic_params):
    dic = []
    for i in reversed(range(map["num_params"])):
        dic += [(str_dic_params[map["param"+str(i)]],range2list(map["range"+str(i)],dic_free_symbols))]
    return dic

def extract_map(map):
    dic = {}
    i = 0
    dict_free_symbol = {}
    for i in range(len(map.params)):
        dic["param"+str(i)] = map.params[i]
        dic["range"+str(i)] = [map.range[i][0],map.range[i][1],map.range[i][2]]
    dic["num_params"] = len(map.params)
    dic["Type"] = "MapEntry"
    return dic
    
def extract_memlet(Memlet):
    dictionary = {}
    dictionary["Volume"] = Memlet.data.volume
    dictionary["Dynamic"] = Memlet.data.dynamic
    if detect_reduction_type(Memlet.data.wcr) is not None:
        dictionary["wcr"] = detect_reduction_type(Memlet.data.wcr)
    else:
        dictionary["wcr"] = 0
    num_range = 0
    if Memlet.data.is_empty():
        dictionary["empty"] = True
    else:
        dictionary["empty"] = False
        if isinstance(Memlet.data.subset, dace.subsets.Indices):
            rng = dace.subsets.Range.from_indices(Memlet.data.subset)
        else:
            rng = Memlet.data.subset
        for rge in rng.ranges:
            dictionary["Range"+str(num_range)] = rge
            num_range+=1
    dictionary["num_ranges"] = num_range
    return dictionary

def range2str(rge):
    return str(rge[0])+"RANGESEP"+str(rge[1])+"RANGESEP"+str(rge[2])

def mem2str(memlet):
    if memlet["empty"]:
        return "EMPTYMEMLET"
    text = str(int(memlet["Dynamic"]))
    text += "SEPMEM1"
    text += str(memlet["Volume"])
    text += "SEPMEM2"
    count = 0
    while "Range"+str(count) in memlet:
        text += range2str(memlet["Range"+str(count)])+"SEPMEM3"
        count += 1
    return text

def map2str(map):
    map_str = ""
    for i in map:
        map_str += i[0]+"SEPMAP1"+range2str(i[1])+"SEPMAP2"
    return map_str


class Encoder():
    def __init__(self,max_free_symbols,max_param,max_map_entry):
        self.dic = {}
        self.dic_params = {}
        self.dic_sym = {}
        count = 1
        for i in ["RANGESEP","SEPMEM1","SEPMEM2","SEPMEM3","SEPMAP1","SEPMAP2","MEMSEPIN","MEMSEPOUT","EMPTYMEMLET"]:
            self.dic[i] = count
            count += 1
        for i in [0,1,2,3,4,5,6,7,8,9]:
            self.dic[str(i)] = count
            count += 1
        self.ops = ["-","~","**","*","+",",","/",":","(",")","ceiling","floor","Mod","Min","Max","int_ceil","int_D","int_floor"]
        for i in self.ops:
            self.dic[i] = count
            count += 1
        for i in range(max_free_symbols):
            self.dic_sym["N"+str(i)] = count
            count += 1
        for i in range(max_map_entry):
            for j in range(max_param):
                self.dic_params["i"+str(i)+str(j)] = count
                count += 1
        self.len = count

    def shuffle_sym(self):
        l = list(self.dic_sym.items())
        random.shuffle(l)
        self.dic_sym = dict(self.dic_sym)

    def __len__(self):
        return self.len


    def encode(self,text):
        if text == "":
            return []
        if text[0:1] == " ":
            return self.encode(text[1:])
        for i in self.dic:
            if text.startswith(i):
                return [self.dic[i]]+self.encode(text[len(i):])
        for i in self.dic_params:
            if text.startswith(i):
                return [self.dic_params[i]]+self.encode(text[len(i):])
        for i in self.dic_sym:
            if text.startswith(i):
                return [self.dic_sym[i]]+self.encode(text[len(i):])
        raise Exception("Invalid state")