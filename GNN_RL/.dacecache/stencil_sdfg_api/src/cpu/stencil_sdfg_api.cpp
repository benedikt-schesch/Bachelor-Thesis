/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_stencil_sdfg_api_internal(float * __restrict__ A, int H, int MAXITER, int W)
{
    float *tmp = new float DACE_ALIGN(64)[(H * W)];
    long long i;

    {
        
        
        {
            #pragma omp parallel for
            for (auto y = 0; y < W; y += 1) {
                for (auto x = 0; x < H; x += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (reset_tmp)
                        out = dace::float32(0);
                        ///////////////////

                        tmp[((W * y) + x)] = out;
                    }
                }
            }
        }
    }
    for (i = 0; (i < MAXITER); i = (i + 1)) {
        {
            
            
            {
                #pragma omp parallel for
                for (auto tile_y = 0; tile_y < int_ceil((W - 2), 128); tile_y += 1) {
                    for (auto tile_x = 0; tile_x < int_ceil((H - 2), 128); tile_x += 1) {
                        {
                            for (auto y = ((128 * tile_y) + 1); y < min((W - 1), ((128 * tile_y) + 129)); y += 1) {
                                for (auto x = ((128 * tile_x) + 1); x < min((H - 1), ((128 * tile_x) + 129)); x += 1) {
                                    {
                                        float c = A[((W * y) + x)];
                                        float e = A[(((W * y) + x) + 1)];
                                        float n = A[((W * (y - 1)) + x)];
                                        float s = A[((W * (y + 1)) + x)];
                                        float w = A[(((W * y) + x) - 1)];
                                        float o;

                                        ///////////////////
                                        // Tasklet code (stencil1)
                                        o = (((((n + s) + w) + e) + c) * dace::float32(0.2));
                                        ///////////////////

                                        tmp[((W * y) + x)] = o;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto y = 1; y < (W - 1); y += 1) {
                    for (auto x = 1; x < (H - 1); x += 1) {
                        {
                            float c = tmp[((W * y) + x)];
                            float e = tmp[(((W * y) + x) + 1)];
                            float n = tmp[((W * (y - 1)) + x)];
                            float s = tmp[((W * (y + 1)) + x)];
                            float w = tmp[(((W * y) + x) - 1)];
                            float o;

                            ///////////////////
                            // Tasklet code (stencil2)
                            o = (((((n + s) + w) + e) + c) * dace::float32(0.2));
                            ///////////////////

                            A[((W * y) + x)] = o;
                        }
                    }
                }
            }
        }
    }
    delete[] tmp;
}

DACE_EXPORTED void __program_stencil_sdfg_api(float * __restrict__ A, int H, int MAXITER, int W)
{
    __program_stencil_sdfg_api_internal(A, H, MAXITER, W);
}

DACE_EXPORTED int __dace_init_stencil_sdfg_api(float * __restrict__ A, int H, int MAXITER, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_stencil_sdfg_api(float * __restrict__ A, int H, int MAXITER, int W)
{
}

