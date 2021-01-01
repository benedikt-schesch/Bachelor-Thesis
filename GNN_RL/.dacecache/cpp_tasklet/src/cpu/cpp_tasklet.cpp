/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_cpp_tasklet_internal(unsigned int * __restrict__ A, unsigned int * __restrict__ B)
{

    {
        
        
        {
            unsigned int a = A[0];
            unsigned int b;

            ///////////////////

            b = a;
            printf("I have been added as raw C++ code\n");

            ///////////////////

            B[0] = b;
        }
    }
}

DACE_EXPORTED void __program_cpp_tasklet(unsigned int * __restrict__ A, unsigned int * __restrict__ B)
{
    __program_cpp_tasklet_internal(A, B);
}

DACE_EXPORTED int __dace_init_cpp_tasklet(unsigned int * __restrict__ A, unsigned int * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_cpp_tasklet(unsigned int * __restrict__ A, unsigned int * __restrict__ B)
{
}

