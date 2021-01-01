/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_inline_noinput_internal(double * __restrict__ A)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 1; i += 1) {
                {
                    double o1;
                    double o2;

                    ///////////////////
                    // Tasklet code (internal_8)
                    o1 = 5;
                    o2 = 3;
                    ///////////////////

                    A[0] = o1;
                    A[1] = o2;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map inline_noinput_17", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/inline_noinput/perf");
}

DACE_EXPORTED void __program_inline_noinput(double * __restrict__ A)
{
    __program_inline_noinput_internal(A);
}

DACE_EXPORTED int __dace_init_inline_noinput(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_inline_noinput(double * __restrict__ A)
{
}

