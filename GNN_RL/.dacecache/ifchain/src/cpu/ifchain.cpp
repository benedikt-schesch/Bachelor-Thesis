/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_ifchain_internal(float * __restrict__ A)
{

    if ((A[0] > 0)) {
        goto __state_0_s20_8;
    }
    if ((! (A[0] > 0))) {
        goto __state_0_if_guard_5;
    }
    __state_0_s20_8:;
    {
        
        
        {
            float o;

            ///////////////////
            // Tasklet code (mytask)
            o = 0;
            ///////////////////

            A[0] = o;
        }
    }
    __state_0_if_guard_5:;
    if ((A[0] > 1)) {
        goto __state_0_s27_8;
    }
    if ((! (A[0] > 1))) {
        goto __state_0_if_guard_9;
    }
    __state_0_s27_8:;
    {
        
        
        {
            float o;

            ///////////////////
            // Tasklet code (mytask)
            o = 1;
            ///////////////////

            A[0] = o;
        }
    }
    __state_0_if_guard_9:;
    if ((A[0] > 0)) {
        {
            
            
            {
                float o;

                ///////////////////
                // Tasklet code (mytask)
                o = (- 5);
                ///////////////////

                A[0] = o;
            }
        }
    } else {
        {
            
            
            {
                float o;

                ///////////////////
                // Tasklet code (mytask)
                o = 9;
                ///////////////////

                A[0] = o;
            }
        }
    }
}

DACE_EXPORTED void __program_ifchain(float * __restrict__ A)
{
    __program_ifchain_internal(A);
}

DACE_EXPORTED int __dace_init_ifchain(float * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_ifchain(float * __restrict__ A)
{
}

