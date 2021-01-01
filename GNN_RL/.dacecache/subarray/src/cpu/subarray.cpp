/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_subarray_internal(double * __restrict__ A, double * __restrict__ B, int W)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    double* a = &A[(13 * i)];
                    double* a2 = &A[(39 * i)];
                    double* b = B + (31 * i);

                    ///////////////////
                    // Tasklet code (subarrays)
                    b[(9 * i)] = (a[(27 * i)] + a2[i]);
                    ///////////////////

                }
            }
        }
    }
}

DACE_EXPORTED void __program_subarray(double * __restrict__ A, double * __restrict__ B, int W)
{
    __program_subarray_internal(A, B, W);
}

DACE_EXPORTED int __dace_init_subarray(double * __restrict__ A, double * __restrict__ B, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_subarray(double * __restrict__ A, double * __restrict__ B, int W)
{
}

