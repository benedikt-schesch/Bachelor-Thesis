/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_strided_range_test_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 4; i += 1) {
                {
                    float* a = &A[((8 * i) + 67)];
                    float* b = B + (4 * i);

                    ///////////////////
                    // Tasklet code (srtest)
                    b[0] = (a[0] * 2);
                    b[1] = (a[4] * 2);
                    b[2] = (a[32] * 2);
                    b[3] = (a[36] * 2);
                    ///////////////////

                }
            }
        }
    }
}

DACE_EXPORTED void __program_strided_range_test(float * __restrict__ A, float * __restrict__ B)
{
    __program_strided_range_test_internal(A, B);
}

DACE_EXPORTED int __dace_init_strided_range_test(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_strided_range_test(float * __restrict__ A, float * __restrict__ B)
{
}

