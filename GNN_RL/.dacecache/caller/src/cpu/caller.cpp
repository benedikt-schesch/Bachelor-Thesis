/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_caller_internal(float * __restrict__ A)
{

    {
        
        
        {
            float i = A[2];

            ///////////////////
            // Tasklet code (p)
            printf("hello world %f\n", i);
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_caller(float * __restrict__ A)
{
    __program_caller_internal(A);
}

DACE_EXPORTED int __dace_init_caller(float * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_caller(float * __restrict__ A)
{
}

