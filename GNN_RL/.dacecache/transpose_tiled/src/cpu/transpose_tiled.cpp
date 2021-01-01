/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_transpose_tiled_internal(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < H; tile_i += 1) {
                for (auto tile_tile_j = 0; tile_tile_j < W; tile_tile_j += 4) {
                    {
                        for (auto tile_j = tile_tile_j; tile_j < (min((W - 1), (tile_tile_j + 3)) + 1); tile_j += TW) {
                            {
                                for (auto i = 0; i < TH; i += 1) {
                                    for (auto j = 0; j < TW; j += 1) {
                                        {
                                            float a = A[(((W * (j + tile_j)) + i) + tile_i)];
                                            float b;

                                            ///////////////////
                                            // Tasklet code (compute_tile)
                                            b = a;
                                            ///////////////////

                                            B[(((W * (i + tile_i)) + j) + tile_j)] = b;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
            dace::perf::report.add("timer_Map compute", __dace_tdiff_0_0_7.count());
        }
    }
    dace::perf::report.save(".dacecache/transpose_tiled/perf");
}

DACE_EXPORTED void __program_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W)
{
    __program_transpose_tiled_internal(A, B, H, TH, TW, W);
}

DACE_EXPORTED int __dace_init_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W)
{
}

