/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_transpose_add_internal(float * __restrict__ A, float * __restrict__ B, int K, int M)
{
    dace::perf::report.reset();
    long long transpose_add_11_4___tmp1[1]  DACE_ALIGN(64);

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < M; i += 1) {
                for (auto j = 0; j < K; j += 1) {
                    float transpose_add_11_4___tmp2[1]  DACE_ALIGN(64);
                    {
                        long long out;

                        ///////////////////
                        // Tasklet code (init___tmp1)
                        out = 1;
                        ///////////////////

                        transpose_add_11_4___tmp1[0] = out;
                    }
                    {
                        long long s2 = transpose_add_11_4___tmp1[0];
                        float s1 = A[((K * i) + j)];
                        float s3;

                        ///////////////////
                        // Tasklet code (_SSAdd_)
                        s3 = (s1 + s2);
                        ///////////////////

                        transpose_add_11_4___tmp2[0] = s3;
                    }
                    {
                        float __inp = transpose_add_11_4___tmp2[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (assign_12_8)
                        __out = __inp;
                        ///////////////////

                        B[((M * j) + i)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map transpose_add_11", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/transpose_add/perf");
}

DACE_EXPORTED void __program_transpose_add(float * __restrict__ A, float * __restrict__ B, int K, int M)
{
    __program_transpose_add_internal(A, B, K, M);
}

DACE_EXPORTED int __dace_init_transpose_add(float * __restrict__ A, float * __restrict__ B, int K, int M)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_transpose_add(float * __restrict__ A, float * __restrict__ B, int K, int M)
{
}

