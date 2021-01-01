/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_nottest_internal(bool * __restrict__ A, bool * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    {
                        bool __in1 = A[((5 * __i0) + __i1)];
                        bool __out;

                        ///////////////////
                        // Tasklet code (_Not_)
                        __out = (! __in1);
                        ///////////////////

                        B[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_nottest(bool * __restrict__ A, bool * __restrict__ B)
{
    __program_nottest_internal(A, B);
}

DACE_EXPORTED int __dace_init_nottest(bool * __restrict__ A, bool * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nottest(bool * __restrict__ A, bool * __restrict__ B)
{
}

