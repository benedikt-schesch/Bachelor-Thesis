/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_foo123_internal(float * __restrict__ a, float * __restrict__ b)
{

    {
        
        
        {
            float __inp = a[0];
            float __out;

            ///////////////////
            // Tasklet code (assign_8_4)
            __out = __inp;
            ///////////////////

            b[0] = __out;
        }
    }
}

DACE_EXPORTED void __program_foo123(float * __restrict__ a, float * __restrict__ b)
{
    __program_foo123_internal(a, b);
}

DACE_EXPORTED int __dace_init_foo123(float * __restrict__ a, float * __restrict__ b)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_foo123(float * __restrict__ a, float * __restrict__ b)
{
}

