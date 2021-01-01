/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_eyetest_internal(double * __restrict__ __return, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < N; j += 1) {
                    {
                        double val;

                        ///////////////////
                        // Tasklet code (eye)
                        val = ((i == (j - 2)) ? 1 : 0);
                        ///////////////////

                        __return[((N * i) + j)] = val;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map eye_map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/eyetest/perf");
}

DACE_EXPORTED void __program_eyetest(double * __restrict__ __return, int N)
{
    __program_eyetest_internal(__return, N);
}

DACE_EXPORTED int __dace_init_eyetest(double * __restrict__ __return, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_eyetest(double * __restrict__ __return, int N)
{
}

