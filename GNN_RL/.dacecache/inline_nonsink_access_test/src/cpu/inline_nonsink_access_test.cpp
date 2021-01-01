/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_inline_nonsink_access_test_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            float o;

            ///////////////////
            // Tasklet code (init)
            o = 2;
            ///////////////////

            A[0] = o;
        }
        {
            float i = A[0];
            float o;

            ///////////////////
            // Tasklet code (square)
            o = (i * i);
            ///////////////////

            A[0] = o;
        }
        {
            float i = A[0];
            float o;

            ///////////////////
            // Tasklet code (cube)
            o = ((i * i) * i);
            ///////////////////

            B[0] = o;
        }
        {
            float a = A[0];
            float b = B[0];
            float c;

            ///////////////////
            // Tasklet code (add)
            c = (a + b);
            ///////////////////

            B[0] = c;
        }
    }
}

DACE_EXPORTED void __program_inline_nonsink_access_test(float * __restrict__ A, float * __restrict__ B)
{
    __program_inline_nonsink_access_test_internal(A, B);
}

DACE_EXPORTED int __dace_init_inline_nonsink_access_test(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_inline_nonsink_access_test(float * __restrict__ A, float * __restrict__ B)
{
}

