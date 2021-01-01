/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void vecAdd_graph_0_0_3(dace::vec<float, 4>* _x, dace::vec<float, 4>* _y, dace::vec<float, 4>* _res, int n) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < (n / 4); i += 1) {
                {
                    dace::vec<float, 4> x_con = _x[i];
                    dace::vec<float, 4> y_con = _y[i];
                    dace::vec<float, 4> z_con;

                    ///////////////////
                    // Tasklet code (vecAdd_task)
                    z_con = (x_con + y_con);
                    ///////////////////

                    _res[i] = z_con;
                }
            }
        }
    }
    
}

void __program_saxpy_test_internal(float * __restrict__ x1, float * __restrict__ y1, float * __restrict__ z1, int n)
{

    {
        
        
        vecAdd_graph_0_0_3((dace::vec<float, 4>*)(&x1[0]), (dace::vec<float, 4>*)(&y1[0]), (dace::vec<float, 4>*)(&z1[0]), n);
    }
}

DACE_EXPORTED void __program_saxpy_test(float * __restrict__ x1, float * __restrict__ y1, float * __restrict__ z1, int n)
{
    __program_saxpy_test_internal(x1, y1, z1, n);
}

DACE_EXPORTED int __dace_init_saxpy_test(float * __restrict__ x1, float * __restrict__ y1, float * __restrict__ z1, int n)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_saxpy_test(float * __restrict__ x1, float * __restrict__ y1, float * __restrict__ z1, int n)
{
}

