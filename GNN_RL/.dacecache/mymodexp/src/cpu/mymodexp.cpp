/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_mymodexp_internal(float * __restrict__ A, float * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    float a = A[(i % N)];
                    float b;

                    ///////////////////
                    // Tasklet code (mytasklet)
                    b = dace::math::exp(a);
                    ///////////////////

                    B[i] = b;
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map mytasklet_map", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/mymodexp/perf");
}

DACE_EXPORTED void __program_mymodexp(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_mymodexp_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_mymodexp(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mymodexp(float * __restrict__ A, float * __restrict__ B, int N)
{
}

