/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

constexpr int size = 20;
constexpr float factor = 4;

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_program_internal(double * __restrict__ input, double * __restrict__ output)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    double a = input[i];
                    double b;

                    ///////////////////
                    // Tasklet code (tasklet)
                    b = (a * 4.0);
                    ///////////////////

                    output[i] = b;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map tasklet", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/program/perf");
}

DACE_EXPORTED void __program_program(double * __restrict__ input, double * __restrict__ output)
{
    __program_program_internal(input, output);
}

DACE_EXPORTED int __dace_init_program(double * __restrict__ input, double * __restrict__ output)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_program(double * __restrict__ input, double * __restrict__ output)
{
}

