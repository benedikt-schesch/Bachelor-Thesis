/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void sdfg_internal_0_0_4(float& input, float* output) {
    long long k;

    {
        
        
        {
            float out;

            ///////////////////
            // Tasklet code (init)
            out = input;
            ///////////////////

            output[0] = out;
        }
    }
    for (k = 0; (k < 4); k = (k + 1)) {
        {
            
            
            {
                float oin = output[0];
                float out;

                ///////////////////
                // Tasklet code (do)
                out = (oin * input);
                ///////////////////

                output[0] = out;
            }
        }
    }
    
}

void __program_outer_sdfg_internal(float * __restrict__ A, float * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < N; j += 1) {
                    sdfg_internal_0_0_4(A[((N * i) + j)], &B[((N * i) + j)]);
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map elements", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/outer_sdfg/perf");
}

DACE_EXPORTED void __program_outer_sdfg(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_outer_sdfg_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_outer_sdfg(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_outer_sdfg(float * __restrict__ A, float * __restrict__ B, int N)
{
}

