/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

constexpr float kernel[9] = {0.0, -1.0, 0.0, -1.0, 0.0, -1.0, 0.0, -1.0, 0.0};

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_stencil3x3_internal(float * __restrict__ A, float * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto y = 1; y < (N - 1); y += 1) {
                for (auto x = 1; x < (N - 1); x += 1) {
                    {
                        float* input = &A[(((N * (y - 1)) + x) - 1)];
                        float out;

                        ///////////////////
                        // Tasklet code (a2b)
                        out = (((((((((kernel[0] * input[0]) + (kernel[1] * input[1])) + (kernel[2] * input[2])) + (kernel[3] * input[N])) + (kernel[4] * input[(N + 1)])) + (kernel[5] * input[(N + 2)])) + (kernel[6] * input[(2 * N)])) + (kernel[7] * input[((2 * N) + 1)])) + (kernel[8] * input[((2 * N) + 2)]));
                        ///////////////////

                        B[((N * y) + x)] = out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map a2b", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/stencil3x3/perf");
}

DACE_EXPORTED void __program_stencil3x3(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_stencil3x3_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_stencil3x3(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_stencil3x3(float * __restrict__ A, float * __restrict__ B, int N)
{
}

