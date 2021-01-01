/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_multiple_tasklets_internal(int * __restrict__ A, int * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 2) {
                {
                    int a = A[i];
                    int b;

                    ///////////////////
                    // Tasklet code (task1)
                    b = (5 * a);
                    ///////////////////

                    B[i] = b;
                }
                {
                    int a = A[(i + 1)];
                    int b;

                    ///////////////////
                    // Tasklet code (task2)
                    b = ((((a + a) + a) + a) + a);
                    ///////////////////

                    B[(i + 1)] = b;
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map mymap", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/multiple_tasklets/perf");
}

DACE_EXPORTED void __program_multiple_tasklets(int * __restrict__ A, int * __restrict__ B, int N)
{
    __program_multiple_tasklets_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_multiple_tasklets(int * __restrict__ A, int * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_multiple_tasklets(int * __restrict__ A, int * __restrict__ B, int N)
{
}

