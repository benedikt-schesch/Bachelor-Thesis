/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void nested_iee_test_0_0_5(float* local, float* m) {

    {
        
        
        {
            float l;

            ///////////////////
            // Tasklet code (init_local)
            l = 2;
            ///////////////////

            local[0] = l;
        }
        {
            float l = local[0];
            float mm;

            ///////////////////
            // Tasklet code (set_m)
            mm = (l + 5);
            ///////////////////

            m[0] = mm;
        }
    }
    
}

void __program_inline_external_edges_test_internal(float * __restrict__ L, float * __restrict__ M)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                nested_iee_test_0_0_5(&L[i], &M[i]);
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map Nested_map", __dace_tdiff_0_0_3.count());
        }
    }
    dace::perf::report.save(".dacecache/inline_external_edges_test/perf");
}

DACE_EXPORTED void __program_inline_external_edges_test(float * __restrict__ L, float * __restrict__ M)
{
    __program_inline_external_edges_test_internal(L, M);
}

DACE_EXPORTED int __dace_init_inline_external_edges_test(float * __restrict__ L, float * __restrict__ M)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_inline_external_edges_test(float * __restrict__ L, float * __restrict__ M)
{
}

