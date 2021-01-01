/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_multiple_cr_internal(long long * __restrict__ A, long long * __restrict__ p, long long * __restrict__ s, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    long long a = A[i];
                    long long b;

                    ///////////////////
                    // Tasklet code (task1)
                    b = a;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, long long>::reduce_atomic(s, b);
                }
                {
                    long long a = A[i];
                    long long b;

                    ///////////////////
                    // Tasklet code (task2)
                    b = a;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Product, long long>::reduce_atomic(p, b);
                }
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map mymap", __dace_tdiff_0_0_3.count());
        }
    }
    dace::perf::report.save(".dacecache/multiple_cr/perf");
}

DACE_EXPORTED void __program_multiple_cr(long long * __restrict__ A, long long * __restrict__ p, long long * __restrict__ s, int N)
{
    __program_multiple_cr_internal(A, p, s, N);
}

DACE_EXPORTED int __dace_init_multiple_cr(long long * __restrict__ A, long long * __restrict__ p, long long * __restrict__ s, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_multiple_cr(long long * __restrict__ A, long long * __restrict__ p, long long * __restrict__ s, int N)
{
}

