/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_extmodtest_internal(float * __restrict__ A, float * __restrict__ result, int H, int W)
{
    dace::perf::report.reset();

    {
        float *tmp = new float DACE_ALIGN(64)[(H * W)];
        
        
        {
            auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    {
                        float a = A[((H * j) + i)];
                        float b;

                        ///////////////////
                        // Tasklet code (compute)
                        b = a;
                        ///////////////////

                        tmp[((W * i) + j)] = b;
                    }
                }
            }
            auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
            dace::perf::report.add("timer_Map compute", __dace_tdiff_0_0_4.count());
        }
        {
            float a = tmp[(W + 2)];
            float b;

            ///////////////////
            // Tasklet code (extmodtest_22)
            b = a;
            ///////////////////

            result[0] = b;
        }
        delete[] tmp;
    }
    dace::perf::report.save(".dacecache/extmodtest/perf");
}

DACE_EXPORTED void __program_extmodtest(float * __restrict__ A, float * __restrict__ result, int H, int W)
{
    __program_extmodtest_internal(A, result, H, W);
}

DACE_EXPORTED int __dace_init_extmodtest(float * __restrict__ A, float * __restrict__ result, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_extmodtest(float * __restrict__ A, float * __restrict__ result, int H, int W)
{
}

