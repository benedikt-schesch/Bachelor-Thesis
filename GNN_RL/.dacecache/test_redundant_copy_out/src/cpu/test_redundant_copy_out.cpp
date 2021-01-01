/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void transpose_sdfg_0_0_2(float* _inp, float* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 3; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 3; __i1 += 1) {
                    {
                        float __inp = _inp[((3 * __i0) + __i1)];
                        float __out;

                        ///////////////////
                        // Tasklet code (transpose)
                        __out = __inp;
                        ///////////////////

                        _out[(__i0 + (3 * __i1))] = __out;
                    }
                }
            }
        }
    }
    
}

void __program_test_redundant_copy_out_internal(float * __restrict__ A, float * __restrict__ D)
{

    {
        
        
        transpose_sdfg_0_0_2(&A[0], &D[0]);
    }
}

DACE_EXPORTED void __program_test_redundant_copy_out(float * __restrict__ A, float * __restrict__ D)
{
    __program_test_redundant_copy_out_internal(A, D);
}

DACE_EXPORTED int __dace_init_test_redundant_copy_out(float * __restrict__ A, float * __restrict__ D)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_redundant_copy_out(float * __restrict__ A, float * __restrict__ D)
{
}

