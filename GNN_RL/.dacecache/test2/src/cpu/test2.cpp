/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_test2_internal(float * __restrict__ C, float * __restrict__ E, float * __restrict__ F)
{

    {
        
        
        {
            float ci = C[0];
            float co;

            ///////////////////
            // Tasklet code (test2_23)
            co = (ci + 1);
            ///////////////////

            C[0] = co;
        }
        {
            float c = C[0];
            float e;

            ///////////////////
            // Tasklet code (test2_28)
            e = c;
            ///////////////////

            E[0] = e;
        }
        {
            float c = C[0];
            float f;

            ///////////////////
            // Tasklet code (test2_33)
            f = c;
            ///////////////////

            F[0] = f;
        }
    }
}

DACE_EXPORTED void __program_test2(float * __restrict__ C, float * __restrict__ E, float * __restrict__ F)
{
    __program_test2_internal(C, E, F);
}

DACE_EXPORTED int __dace_init_test2(float * __restrict__ C, float * __restrict__ E, float * __restrict__ F)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test2(float * __restrict__ C, float * __restrict__ E, float * __restrict__ F)
{
}

