/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_whiletest_internal(int * __restrict__ A)
{

    while ((A[0] > 0)) {
        {
            
            
            {
                int a = A[0];
                int b;

                ///////////////////
                // Tasklet code (whiletest_8)
                b = (a - 1);
                ///////////////////

                A[0] = b;
            }
        }
    }
}

DACE_EXPORTED void __program_whiletest(int * __restrict__ A)
{
    __program_whiletest_internal(A);
}

DACE_EXPORTED int __dace_init_whiletest(int * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_whiletest(int * __restrict__ A)
{
}

