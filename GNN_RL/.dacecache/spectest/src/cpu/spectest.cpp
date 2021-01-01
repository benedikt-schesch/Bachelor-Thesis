/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

constexpr int N = 20;
constexpr int M = 30;

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_spectest_internal(float * __restrict__ A, float * __restrict__ B)
{
    dace::perf::report.reset();

    {
        float *At = new float DACE_ALIGN(64)[(M * (N - 2))];
        
        

        dace::CopyND<float, 1, false, (M * (N - 2))>::template ConstDst<1>::Copy(
        A + M, At, 1);
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 1; i < (N - 1); i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    {
                        float a = At[((M * (i - 1)) + j)];
                        float b;

                        ///////////////////
                        // Tasklet code (compute)
                        b = dace::math::exp(a);
                        ///////////////////

                        B[((M * i) + j)] = b;
                    }
                }
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map compute_map", __dace_tdiff_0_0_3.count());
        }
        delete[] At;
    }
    dace::perf::report.save(".dacecache/spectest/perf");
}

DACE_EXPORTED void __program_spectest(float * __restrict__ A, float * __restrict__ B)
{
    __program_spectest_internal(A, B);
}

DACE_EXPORTED int __dace_init_spectest(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_spectest(float * __restrict__ A, float * __restrict__ B)
{
}

