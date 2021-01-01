/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_tlstream_internal(float * __restrict__ ga, int N)
{
    dace::perf::report.reset();

    {
        dace::ArrayStreamView<float> gs (ga);
        
        
        {
            auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                float la[10]  DACE_ALIGN(64);
                dace::ArrayStreamViewThreadlocal<float> ls (la);
                {

                    ///////////////////
                    // Tasklet code (arange)
                    ls.push(i);
                    ///////////////////

                }
                gs.push(ls);
            }
            auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
            dace::perf::report.add("timer_Map par", __dace_tdiff_0_0_4.count());
        }
    }
    dace::perf::report.save(".dacecache/tlstream/perf");
}

DACE_EXPORTED void __program_tlstream(float * __restrict__ ga, int N)
{
    __program_tlstream_internal(ga, N);
}

DACE_EXPORTED int __dace_init_tlstream(float * __restrict__ ga, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tlstream(float * __restrict__ ga, int N)
{
}

