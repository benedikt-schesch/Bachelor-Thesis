/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_transpose_test_internal(float * __restrict__ C, float * __restrict__ D)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    {
                        float __inp = C[((20 * i) + j)];
                        float __out;

                        ///////////////////
                        // Tasklet code (assign_12_8)
                        __out = __inp;
                        ///////////////////

                        D[(i + (20 * j))] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map sdfg_transpose_11", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/transpose_test/perf");
}

DACE_EXPORTED void __program_transpose_test(float * __restrict__ C, float * __restrict__ D)
{
    __program_transpose_test_internal(C, D);
}

DACE_EXPORTED int __dace_init_transpose_test(float * __restrict__ C, float * __restrict__ D)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_transpose_test(float * __restrict__ C, float * __restrict__ D)
{
}

