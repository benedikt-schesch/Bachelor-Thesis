/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_custom_code_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{

    {
        
        
        {
            double* inp = &A[310];
            double* out = B;

            ///////////////////
            for (int i0 = 0; i0 < 10; ++i0) {
                for (int i1 = 0; i1 < 20; ++i1) {
                    out[i0 * 30 + i1 * 1] = inp[i0 * 30 + i1 * 1] + 7;
                }
            }
            ///////////////////

        }
        {
            double* inp = &B[0];
            double* out = C;

            ///////////////////
            for (int i0 = 0; i0 < 10; ++i0) {
                for (int i1 = 0; i1 < 20; ++i1) {
                    out[i0 * 30 + i1 * 1] = inp[i0 * 30 + i1 * 1] * 3;
                }
            }
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_custom_code(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
    __program_custom_code_internal(A, B, C);
}

DACE_EXPORTED int __dace_init_custom_code(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_custom_code(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
}

