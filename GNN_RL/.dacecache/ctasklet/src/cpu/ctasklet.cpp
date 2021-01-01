/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_ctasklet_internal(int * __restrict__ A, int * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto k = 0; k < 2; k += 1) {
                {
                    auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
                    for (auto i = 0; i < (N / 2); i += 1) {
                        long long __dace_0_0_6_7_bb;
                        {
                            int aa = A[(i + ((N * k) / 2))];
                            long long bb;

                            ///////////////////
                            // Tasklet code (mytasklet)
                            bb = (5 * aa);
                            ///////////////////

                            __dace_0_0_6_7_bb = bb;
                        }
                        {
                            const long long& cc = __dace_0_0_6_7_bb;
                            int dd;

                            ///////////////////
                            // Tasklet code (mytasklet2)
                            dd = (2 * cc);
                            ///////////////////

                            B[(i + ((N * k) / 2))] = dd;
                        }
                    }
                    auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
                    dace::perf::report.add("timer_Map mymap", __dace_tdiff_0_0_4.count());
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map omap", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/ctasklet/perf");
}

DACE_EXPORTED void __program_ctasklet(int * __restrict__ A, int * __restrict__ B, int N)
{
    __program_ctasklet_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_ctasklet(int * __restrict__ A, int * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_ctasklet(int * __restrict__ A, int * __restrict__ B, int N)
{
}

