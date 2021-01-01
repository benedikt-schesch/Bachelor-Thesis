/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_xchg_internal(int * __restrict__ locked, int * __restrict__ output)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    int l;
                    int out;

                    ///////////////////
                    // Tasklet code (xchg_9)
                    l = dace::wcr_fixed<dace::ReductionType::Exchange, int>::reduce_atomic(locked, 4);
                    out = l;
                    ///////////////////

                    output[i] = out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map xchg_8", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/xchg/perf");
}

DACE_EXPORTED void __program_xchg(int * __restrict__ locked, int * __restrict__ output)
{
    __program_xchg_internal(locked, output);
}

DACE_EXPORTED int __dace_init_xchg(int * __restrict__ locked, int * __restrict__ output)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_xchg(int * __restrict__ locked, int * __restrict__ output)
{
}

