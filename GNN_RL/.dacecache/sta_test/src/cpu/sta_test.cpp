/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_sta_test_internal(float * __restrict__ A, float * __restrict__ inp)
{

    {
        
        
        {
            float a = inp[0];
            float b;

            ///////////////////
            // Tasklet code (seta)
            b = a;
            ///////////////////

            A[0] = b;
        }
    }
    if ((A[0] > 3)) {
        goto __state_0_state_1;
    }
    if ((A[0] <= 3)) {
        goto __state_0_state_2;
    }
    __state_0_state_1:;
    {
        
        
        {
            float a = A[0];

            ///////////////////
            // Tasklet code (geta)
            printf("ok %f\n", (a + 1));
            ///////////////////

        }
    }
    goto __state_exit_0_sdfg;
    __state_0_state_2:;
    {
        
        
        {
            float a = A[0];

            ///////////////////
            // Tasklet code (geta)
            printf("BAD %f\n", (a - 1));
            ///////////////////

        }
    }
    __state_exit_0_sdfg:;
}

DACE_EXPORTED void __program_sta_test(float * __restrict__ A, float * __restrict__ inp)
{
    __program_sta_test_internal(A, inp);
}

DACE_EXPORTED int __dace_init_sta_test(float * __restrict__ A, float * __restrict__ inp)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sta_test(float * __restrict__ A, float * __restrict__ inp)
{
}

