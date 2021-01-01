/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_fusion_with_transient_internal(double * __restrict__ A)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                double __s0_n8OUT_1_n1IN_1[2]  DACE_ALIGN(64);
                {
                    auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
                    for (auto j = 0; j < 2; j += 1) {
                        {
                            double a = A[(i + (20 * j))];
                            double t;

                            ///////////////////
                            // Tasklet code (fusion_with_transient_154_4_156)
                            t = (a * a);
                            ///////////////////

                            __s0_n8OUT_1_n1IN_1[j] = t;
                        }
                    }
                    auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
                    dace::perf::report.add("timer_Map fusion_with_transient_154_4_155", __dace_tdiff_0_0_4.count());
                }
                {
                    auto __dace_tbegin_0_0_6 = std::chrono::high_resolution_clock::now();
                    for (auto j = 0; j < 2; j += 1) {
                        {
                            double t = __s0_n8OUT_1_n1IN_1[j];
                            double o;

                            ///////////////////
                            // Tasklet code (fusion_with_transient_160_4_162)
                            o = (t * 2);
                            ///////////////////

                            A[(i + (20 * j))] = o;
                        }
                    }
                    auto __dace_tend_0_0_6 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_6 = __dace_tend_0_0_6 - __dace_tbegin_0_0_6;
                    dace::perf::report.add("timer_Map fusion_with_transient_160_4_161", __dace_tdiff_0_0_6.count());
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map fusion_with_transient_154", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/fusion_with_transient/perf");
}

DACE_EXPORTED void __program_fusion_with_transient(double * __restrict__ A)
{
    __program_fusion_with_transient_internal(A);
}

DACE_EXPORTED int __dace_init_fusion_with_transient(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_fusion_with_transient(double * __restrict__ A)
{
}

