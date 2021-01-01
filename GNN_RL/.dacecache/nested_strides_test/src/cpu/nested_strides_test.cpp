/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_nested_strides_test_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 3; i += 1) {
                for (auto j = 0; j < 4; j += 1) {
                    {
                        float* a = &A[((4 * i) + j)];
                        float b;

                        ///////////////////
                        // Tasklet code (nested_strides_test_9)
                        b = (a[0] + a[12]);
                        ///////////////////

                        B[((4 * i) + j)] = b;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_nested_strides_test(float * __restrict__ A, float * __restrict__ B)
{
    __program_nested_strides_test_internal(A, B);
}

DACE_EXPORTED int __dace_init_nested_strides_test(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_strides_test(float * __restrict__ A, float * __restrict__ B)
{
}

