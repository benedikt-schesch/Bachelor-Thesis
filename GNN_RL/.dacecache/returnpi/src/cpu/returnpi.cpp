/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_returnpi_internal(double * __restrict__ result)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                {
                    double __out;

                    ///////////////////
                    // Tasklet code (assign_32_4)
                    __out = 3.141592653589793;
                    ///////////////////

                    result[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map assign_32_4_map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/returnpi/perf");
}

DACE_EXPORTED void __program_returnpi(double * __restrict__ result)
{
    __program_returnpi_internal(result);
}

DACE_EXPORTED int __dace_init_returnpi(double * __restrict__ result)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_returnpi(double * __restrict__ result)
{
}

