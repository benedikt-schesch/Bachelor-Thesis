/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_tile_twice_test_internal(double * __restrict__ a)
{
    dace::perf::report.reset();
    double *__tmp0 = new double DACE_ALIGN(64)[1];

    {
        
        
        {
            double out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 2.0;
            ///////////////////

            __tmp0[0] = out;
        }
        {
            auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile___i0 = 0; tile___i0 < int_ceil(200, 5); tile___i0 += 1) {
                {
                    auto __dace_tbegin_0_0_9 = std::chrono::high_resolution_clock::now();
                    for (auto tile1___i0 = 0; tile1___i0 < int_ceil((((- 5) * tile___i0) + min(200, ((5 * tile___i0) + 5))), 4); tile1___i0 += 1) {
                        {
                            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
                            for (auto __i0 = ((4 * tile1___i0) + (5 * tile___i0)); __i0 < min(200, ((5 * tile___i0) + 5), (((4 * tile1___i0) + (5 * tile___i0)) + 4)); __i0 += 1) {
                                {
                                    double __in2 = __tmp0[0];
                                    double __in1 = a[__i0];
                                    double __out;

                                    ///////////////////
                                    // Tasklet code (augassign_10_4)
                                    __out = (__in1 * __in2);
                                    ///////////////////

                                    a[__i0] = __out;
                                }
                            }
                            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
                            dace::perf::report.add("timer_Map augassign_10_4_map", __dace_tdiff_0_0_2.count());
                        }
                    }
                    auto __dace_tend_0_0_9 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_9 = __dace_tend_0_0_9 - __dace_tbegin_0_0_9;
                    dace::perf::report.add("timer_Map tile1___i0_augassign_10_4_map", __dace_tdiff_0_0_9.count());
                }
            }
            auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
            dace::perf::report.add("timer_Map tile___i0_augassign_10_4_map", __dace_tdiff_0_0_7.count());
        }
    }
    delete[] __tmp0;
    dace::perf::report.save(".dacecache/tile_twice_test/perf");
}

DACE_EXPORTED void __program_tile_twice_test(double * __restrict__ a)
{
    __program_tile_twice_test_internal(a);
}

DACE_EXPORTED int __dace_init_tile_twice_test(double * __restrict__ a)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tile_twice_test(double * __restrict__ a)
{
}

