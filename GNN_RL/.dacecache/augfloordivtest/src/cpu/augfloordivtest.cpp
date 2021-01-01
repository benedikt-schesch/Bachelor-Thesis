/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_augfloordivtest_internal(long long * __restrict__ A, long long * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    {
                        long long __in2 = A[((5 * __i0) + __i1)];
                        long long __in1 = B[((5 * __i0) + __i1)];
                        long long __out;

                        ///////////////////
                        // Tasklet code (augassign_28_4)
                        __out = dace::math::ifloor(__in1 / __in2);
                        ///////////////////

                        B[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_augfloordivtest(long long * __restrict__ A, long long * __restrict__ B)
{
    __program_augfloordivtest_internal(A, B);
}

DACE_EXPORTED int __dace_init_augfloordivtest(long long * __restrict__ A, long long * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_augfloordivtest(long long * __restrict__ A, long long * __restrict__ B)
{
}

