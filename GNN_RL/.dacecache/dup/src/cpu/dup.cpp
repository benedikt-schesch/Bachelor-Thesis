/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_dup_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{

    {
        
        
        {
            float c = C[0];
            float d;

            ///////////////////
            // Tasklet code (c_task)
            d = c;
            ///////////////////

            D[0] = d;
        }
        {
            float b = B[0];
            float d = D[0];
            float f;

            ///////////////////
            // Tasklet code (f_task)
            f = (b + d);
            ///////////////////

            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(F, f);
        }
        {
            float a = A[0];
            float d = D[0];
            float e;

            ///////////////////
            // Tasklet code (e_task)
            e = (a + d);
            ///////////////////

            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(E, e);
        }
    }
}

DACE_EXPORTED void __program_dup(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
    __program_dup_internal(A, B, C, D, E, F);
}

DACE_EXPORTED int __dace_init_dup(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dup(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
}

