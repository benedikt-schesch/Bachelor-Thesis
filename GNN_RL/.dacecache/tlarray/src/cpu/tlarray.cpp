/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
#include <omp.h>
namespace dace { namespace perf { Report report; } }
#include <chrono>
int *tmp;
#pragma omp threadprivate(tmp)
void __program_tlarray_internal(int * __restrict__ A)
{
    dace::perf::report.reset();

    {

        #pragma omp parallel
        {
            tmp = new int DACE_ALIGN(64)[128];
        }
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 128; i += 1) {
                {
                    int t;

                    ///////////////////
                    // Tasklet code (tlarray_13)
                    t = omp_get_thread_num();
                    ///////////////////

                    tmp[i] = t;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map tlarray_12", __dace_tdiff_0_0_0.count());
        }
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 128; i += 1) {
                {
                    int t = tmp[i];
                    int o;

                    ///////////////////
                    // Tasklet code (tlarray_19)
                    o = t;
                    ///////////////////

                    A[i] = o;
                }
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map tlarray_18", __dace_tdiff_0_0_3.count());
        }
        #pragma omp parallel
        {
            delete[] tmp;
        }
    }
    dace::perf::report.save(".dacecache/tlarray/perf");
}

DACE_EXPORTED void __program_tlarray(int * __restrict__ A)
{
    __program_tlarray_internal(A);
}

DACE_EXPORTED int __dace_init_tlarray(int * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tlarray(int * __restrict__ A)
{
}

