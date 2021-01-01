/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_arange_internal(int * __restrict__ __return, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_5 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < int_ceil(N, 5); tile_i += 1) {
                int trans___return[5]  DACE_ALIGN(64);
                {
                    auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
                    for (auto i = (5 * tile_i); i < min(N, ((5 * tile_i) + 5)); i += 1) {
                        {
                            int o;

                            ///////////////////
                            // Tasklet code (arange_14)
                            o = i;
                            ///////////////////

                            trans___return[(i - (5 * tile_i))] = o;
                        }
                    }
                    auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
                    dace::perf::report.add("timer_Map arange_13", __dace_tdiff_0_0_0.count());
                }

                dace::CopyNDDynamic<int, 1, false, 1>::template ConstDst<1>::Copy(
                trans___return, __return + (5 * tile_i), (((- 5) * tile_i) + min(N, ((5 * tile_i) + 5))), 1);
            }
            auto __dace_tend_0_0_5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_5 = __dace_tend_0_0_5 - __dace_tbegin_0_0_5;
            dace::perf::report.add("timer_Map tile_i_arange_13", __dace_tdiff_0_0_5.count());
        }
    }
    dace::perf::report.save(".dacecache/arange/perf");
}

DACE_EXPORTED void __program_arange(int * __restrict__ __return, int N)
{
    __program_arange_internal(__return, N);
}

DACE_EXPORTED int __dace_init_arange(int * __restrict__ __return, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_arange(int * __restrict__ __return, int N)
{
}

