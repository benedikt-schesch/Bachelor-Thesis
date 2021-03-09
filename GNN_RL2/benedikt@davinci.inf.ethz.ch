import dace
import tqdm

def prog_generator1D(n, b, c,s):
    @dace.program
    def func1(a):
        return a + 2

    @dace.program
    def func2(a):
        return a * 5 + 2 * 5 * a * a

    @dace.program
    def func2D1(a,b):
        return a + b
    
    @dace.program
    def func2D2(a,b):
        return 5*a + 2 + b*a +b*64
    
    func = func1 if b else func2
    func2D = func2D1 if c else func2D2

    @dace.program
    def myprog1(A: dace.float64[n]):
        for i in dace.map[0:n:s]:
            A[i] = func(A[i])
    
    @dace.program
    def myprog2(A: dace.float64[n]):
        res = A[0]
        for i in dace.map[1:n:s]:
            res += A[i]
    
    @dace.program
    def myprog3(A: dace.float64[n]):
        for i in dace.map[1:n:s]:
            A[i] = func2D(A[i],A[i-1])
    
    @dace.program
    def myprog4(A: dace.float64[n]):
        for i in dace.map[0:n:s]:
            for j in dace.map[0:n:s]:
                A[i] += func(A[j])
    return [myprog1,myprog2,myprog3,myprog4]

def prog_generator2D(n, m, b, c, s):
    @dace.program
    def func1(a):
        return a + 2

    @dace.program
    def func2(a):
        return a * 5 + 2 * 5 * a * a

    @dace.program
    def func2D1(a,b):
        return a + b
    
    @dace.program
    def func2D2(a,b):
        return 5*a + 2 + b*a +b*64
    
    func = func1 if b else func2
    func2D = func2D1 if c else func2D2
    @dace.program
    def myprog5(A: dace.float64[n],B: dace.float64[m]):
        for i in dace.map[0:n:s]:
            A[i] = func2D(A[i],B[i])
    
    @dace.program
    def myprog6(A: dace.float64[n],B: dace.float64[m]):
        A[0] = 0
        for i in dace.map[0:n:s]:
            A[0] += func2D(A[i],B[i])
    
    @dace.program
    def myprog7(A: dace.float64[n],B: dace.float64[m]):
        for i in dace.map[0:n:s]:
            for j in dace.map[0:n:s]:
                A[i] += func(B[j])
    @dace.program
    def myprog8(A: dace.float64[n],B: dace.float64[m]):
        for i in dace.map[0:n:s]:
            for j in dace.map[0:n:s]:
                A[i] += func2D(A[j],B[j])
    @dace.program
    def myprog9(A: dace.float64[n],B: dace.float64[m]):
        for i in dace.map[0:n:s]:
            for j in dace.map[0:n:s]:
                A[i] += func2D(A[i],B[j])
    return [myprog5,myprog6,myprog7,myprog8,myprog9]


arr1 = [1,2]#,8,32,64,256,512,1024,2048,dace.symbol('N')]
arr2 = [1]#,2,8,32,64,256,512,1024,2048,dace.symbol('M')]
strides = [1,2]#,4,16,64,128,512]
list_prog = []
for l in arr1:
    for stride in strides:
        list_prog += prog_generator1D(l,False,False,stride)
        list_prog += prog_generator1D(l,False,True,stride)
        list_prog += prog_generator1D(l,True,False,stride)
        list_prog += prog_generator1D(l,True,True,stride)
for m in arr1:
    for n in arr2:
        for stride in strides:
            list_prog += prog_generator2D(m,n,False,False,stride)
            list_prog += prog_generator2D(m,n,False,True,stride)
            list_prog += prog_generator2D(m,n,True,False,stride)
            list_prog += prog_generator2D(m,n,True,True,stride)

for enum,prog in enumerate([list_prog[0]]):
    #export DACE_optimizer_automatic_strict_transformations=False
    print(enum,"/",len(list_prog))
    try:
        #prog.to_sdfg().save('MyEnv/GNN_RL2/SDFGS/program'+str(enum)+'.sdfg')
        prog.to_sdfg().save('_dacegraphs/program'+str(enum)+'.sdfg')
    except Exception:
        continue