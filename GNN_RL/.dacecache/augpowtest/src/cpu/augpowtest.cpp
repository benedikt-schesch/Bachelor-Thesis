/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_augpowtest_internal(long long * __restrict__ A, long long * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    {
                        long long __in2 = A[((5 * __i0) + __i1)];
                        long long __in1 = B[((5 * __i0) + __i1)];
                        long long __out;

                        ///////////////////
                        // Tasklet code (augassign_38_4)
                        __out = dace::math::pow(__in1, __in2);
                        ///////////////////

                        B[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map augassign_38_4_map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/augpowtest/perf");
}

DACE_EXPORTED void __program_augpowtest(long long * __restrict__ A, long long * __restrict__ B)
{
    __program_augpowtest_internal(A, B);
}

DACE_EXPORTED int __dace_init_augpowtest(long long * __restrict__ A, long long * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_augpowtest(long long * __restrict__ A, long long * __restrict__ B)
{
}

