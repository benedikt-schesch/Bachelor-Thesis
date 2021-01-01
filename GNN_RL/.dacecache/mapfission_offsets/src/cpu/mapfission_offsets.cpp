/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_mapfission_offsets_internal(double * __restrict__ A)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_5 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 10; i < 20; i += 1) {
                double interim[1]  DACE_ALIGN(64);
                {
                    double a = A[i];
                    double b;

                    ///////////////////
                    // Tasklet code (addone)
                    b = (a + 1);
                    ///////////////////

                    interim[0] = b;
                }
                {
                    double a = interim[0];
                    double b;

                    ///////////////////
                    // Tasklet code (addtwo)
                    b = (a + 2);
                    ///////////////////

                    A[i] = b;
                }
            }
            auto __dace_tend_0_0_5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_5 = __dace_tend_0_0_5 - __dace_tbegin_0_0_5;
            dace::perf::report.add("timer_Map outer_fused", __dace_tdiff_0_0_5.count());
        }
    }
    dace::perf::report.save(".dacecache/mapfission_offsets/perf");
}

DACE_EXPORTED void __program_mapfission_offsets(double * __restrict__ A)
{
    __program_mapfission_offsets_internal(A);
}

DACE_EXPORTED int __dace_init_mapfission_offsets(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mapfission_offsets(double * __restrict__ A)
{
}

