/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_offset_stride_internal(float * __restrict__ A, float * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 1; i < 4; i += 1) {
                for (auto j = 1; j < 3; j += 1) {
                    {
                        float a = A[(((N * (i + 2)) + j) + 3)];
                        float b;

                        ///////////////////
                        // Tasklet code (mytasklet)
                        b = a;
                        ///////////////////

                        B[(((3 * i) + j) - 4)] = b;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map mymap", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/offset_stride/perf");
}

DACE_EXPORTED void __program_offset_stride(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_offset_stride_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_offset_stride(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_offset_stride(float * __restrict__ A, float * __restrict__ B, int N)
{
}

