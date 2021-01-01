/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_test1_internal(double * __restrict__ A, double * __restrict__ B, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    double input = A[i];
                    double out;

                    ///////////////////
                    // Tasklet code (test1_10)
                    out = (input + 42);
                    ///////////////////

                    A[i] = out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map test1_9", __dace_tdiff_0_0_0.count());
        }

        dace::CopyNDDynamic<double, 1, false, 1>::template ConstDst<1>::Copy(
        A, B, N, 1);
    }
    {
        
        
        {
            auto __dace_tbegin_0_1_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    double input = A[i];
                    double out;

                    ///////////////////
                    // Tasklet code (test1_16)
                    out = (input + 43);
                    ///////////////////

                    A[i] = out;
                }
            }
            auto __dace_tend_0_1_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_0 = __dace_tend_0_1_0 - __dace_tbegin_0_1_0;
            dace::perf::report.add("timer_Map test1_15", __dace_tdiff_0_1_0.count());
        }
    }
    dace::perf::report.save(".dacecache/test1/perf");
}

DACE_EXPORTED void __program_test1(double * __restrict__ A, double * __restrict__ B, int N)
{
    __program_test1_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_test1(double * __restrict__ A, double * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test1(double * __restrict__ A, double * __restrict__ B, int N)
{
}

