/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void reduce_0_0_9(float* _in, float* _out, int H, int W) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < H; _i0 += 1) {
                for (auto _i1 = 0; _i1 < W; _i1 += 1) {
                    {
                        float inp = _in[((W * _i0) + _i1)];
                        float out;

                        ///////////////////
                        // Tasklet code (identity)
                        out = inp;
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_out, out);
                    }
                }
            }
        }
    }
    
}

void __program_mapreduce_test_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
    dace::perf::report.reset();

    {
        float *tmp = new float DACE_ALIGN(64)[(H * W)];
        float *__tmp1 = new float DACE_ALIGN(64)[1];
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    {
                        float a = A[((W * i) + j)];
                        float b;
                        float t;

                        ///////////////////
                        // Tasklet code (compute_tile)
                        b = (a * 5);
                        t = (a * 5);
                        ///////////////////

                        B[((W * i) + j)] = b;
                        tmp[((W * i) + j)] = t;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map compute_tile", __dace_tdiff_0_0_0.count());
        }
        reduce_0_0_9(&tmp[0], &__tmp1[0], H, W);
        {
            float __inp = __tmp1[0];
            float __out;

            ///////////////////
            // Tasklet code (assign_26_4)
            __out = __inp;
            ///////////////////

            sum[0] = __out;
        }
        delete[] tmp;
        delete[] __tmp1;
    }
    dace::perf::report.save(".dacecache/mapreduce_test/perf");
}

DACE_EXPORTED void __program_mapreduce_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
    __program_mapreduce_test_internal(A, B, sum, H, W);
}

DACE_EXPORTED int __dace_init_mapreduce_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mapreduce_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ sum, int H, int W)
{
}

