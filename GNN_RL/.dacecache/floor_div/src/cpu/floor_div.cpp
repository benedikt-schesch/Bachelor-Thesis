/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_floor_div_internal(double * __restrict__ Input, double * __restrict__ Output, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    double inp = Input[(i / 2)];
                    double out;

                    ///////////////////
                    // Tasklet code (div)
                    out = inp;
                    ///////////////////

                    Output[i] = out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map div", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/floor_div/perf");
}

DACE_EXPORTED void __program_floor_div(double * __restrict__ Input, double * __restrict__ Output, int N)
{
    __program_floor_div_internal(Input, Output, N);
}

DACE_EXPORTED int __dace_init_floor_div(double * __restrict__ Input, double * __restrict__ Output, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_floor_div(double * __restrict__ Input, double * __restrict__ Output, int N)
{
}

