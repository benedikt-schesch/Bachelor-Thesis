/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_subrange1_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i1 = 0; __i1 < 4; __i1 += 1) {
                for (auto __i0 = 0; __i0 < 3; __i0 += 1) {
                    {
                        float __in1 = A[((4 * __i0) + __i1)];
                        float __in2 = A[(((4 * __i0) + __i1) + 12)];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        B[((4 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_subrange1(float * __restrict__ A, float * __restrict__ B)
{
    __program_subrange1_internal(A, B);
}

DACE_EXPORTED int __dace_init_subrange1(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_subrange1(float * __restrict__ A, float * __restrict__ B)
{
}

