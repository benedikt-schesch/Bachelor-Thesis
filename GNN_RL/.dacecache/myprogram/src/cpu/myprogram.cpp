/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_myprogram_internal(float * __restrict__ A, float * __restrict__ B, int H, int W)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_5 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < H; tile_i += 1024) {
                for (auto tile_j = 0; tile_j < W; tile_j += 1024) {
                    {
                        for (auto i = tile_i; i < (min((H - 1), (tile_i + 1023)) + 1); i += 1) {
                            for (auto j = tile_j; j < (min((W - 1), (tile_j + 1023)) + 1); j += 1) {
                                {
                                    float a = A[((H * j) + i)];
                                    float b;

                                    ///////////////////
                                    // Tasklet code (compute)
                                    b = a;
                                    ///////////////////

                                    B[((W * i) + j)] = b;
                                }
                            }
                        }
                    }
                }
            }
            auto __dace_tend_0_0_5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_5 = __dace_tend_0_0_5 - __dace_tbegin_0_0_5;
            dace::perf::report.add("timer_Map compute", __dace_tdiff_0_0_5.count());
        }
    }
    dace::perf::report.save(".dacecache/myprogram/perf");
}

DACE_EXPORTED void __program_myprogram(float * __restrict__ A, float * __restrict__ B, int H, int W)
{
    __program_myprogram_internal(A, B, H, W);
}

DACE_EXPORTED int __dace_init_myprogram(float * __restrict__ A, float * __restrict__ B, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_myprogram(float * __restrict__ A, float * __restrict__ B, int H, int W)
{
}

