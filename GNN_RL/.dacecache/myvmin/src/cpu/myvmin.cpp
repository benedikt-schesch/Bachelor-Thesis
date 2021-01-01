/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_myvmin_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 2) {
                {
                    dace::vec<float, 2> a = *(dace::vec<float, 2> *)(&A[i]);
                    dace::vec<float, 2> b = *(dace::vec<float, 2> *)(&B[i]);
                    dace::vec<float, 2> c;

                    ///////////////////
                    // Tasklet code (mytasklet)
                    c = min(a, b);
                    ///////////////////

                    *(dace::vec<float, 2> *)(&C[i]) = c;
                }
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map mytasklet_map", __dace_tdiff_0_0_3.count());
        }
    }
    dace::perf::report.save(".dacecache/myvmin/perf");
}

DACE_EXPORTED void __program_myvmin(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, int N)
{
    __program_myvmin_internal(A, B, C, N);
}

DACE_EXPORTED int __dace_init_myvmin(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_myvmin(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, int N)
{
}

