from dace.sdfg.sdfg import SDFG
import dace


paths = ['/Users/benediktschesch/MyEnv/tests/.dacecache/test8/program.sdfg']
for file in paths:
    try:
        sdfg = dace.SDFG.from_file(file)
    except:
        print("Not Valid SDFG at: "+str(file))
        continue
    state = sdfg.states()[0]
    dic = {dace.symbol("N"):"N0"}
    sdfg.replace("N","N0")
    sdfg.replace("i","i00")
    sdfg.save("/Users/benediktschesch/MyEnv/data.sdfg")
    state.nodes()[2].range[0][1] = state.nodes()[2].range[0][1].subs(dic)
    state.nodes()[2].params[0] = "i00"
    state.nodes()[3]
    for state in sdfg.states():
        print("test")