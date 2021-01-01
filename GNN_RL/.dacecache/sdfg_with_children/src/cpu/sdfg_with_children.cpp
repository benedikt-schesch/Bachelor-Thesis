/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void elements_13_4_0_0_2(float* __tmp_17_19, float* __tmp_18_19) {
    long long k;

    {
        
        
        {
            float inp = __tmp_17_19[0];
            float out;

            ///////////////////
            // Tasklet code (init)
            out = inp;
            ///////////////////

            __tmp_18_19[0] = out;
        }
    }
    for (k = 0; (k < 4); k = (k + 1)) {
        {
            
            
            {
                float inp = __tmp_17_19[0];
                float oin = __tmp_18_19[0];
                float out;

                ///////////////////
                // Tasklet code (do)
                out = (oin * inp);
                ///////////////////

                __tmp_18_19[0] = out;
            }
        }
    }
    
}

void __program_sdfg_with_children_internal(float * __restrict__ A, float * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < N; j += 1) {
                    elements_13_4_0_0_2(&A[((N * i) + j)], &B[((N * i) + j)]);
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map elements", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/sdfg_with_children/perf");
}

DACE_EXPORTED void __program_sdfg_with_children(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_sdfg_with_children_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_sdfg_with_children(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sdfg_with_children(float * __restrict__ A, float * __restrict__ B, int N)
{
}

