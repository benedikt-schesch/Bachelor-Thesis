/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_tovec_internal(dace::vec<double, 2> * __restrict__ A, dace::vec<double, 2> * __restrict__ __return)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 19; __i0 += 2) {
                {
                    dace::vec<double, 2> __in1 = A[(__i0 / 2)];
                    dace::vec<double, 2> __in2 = A[(__i0 / 2)];
                    dace::vec<double, 2> __out;

                    ///////////////////
                    // Tasklet code (_Add_)
                    __out = (__in1 + __in2);
                    ///////////////////

                    __return[(__i0 / 2)] = __out;
                }
            }
        }
    }
}

DACE_EXPORTED void __program_tovec(dace::vec<double, 2> * __restrict__ A, dace::vec<double, 2> * __restrict__ __return)
{
    __program_tovec_internal(A, __return);
}

DACE_EXPORTED int __dace_init_tovec(dace::vec<double, 2> * __restrict__ A, dace::vec<double, 2> * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tovec(dace::vec<double, 2> * __restrict__ A, dace::vec<double, 2> * __restrict__ __return)
{
}

