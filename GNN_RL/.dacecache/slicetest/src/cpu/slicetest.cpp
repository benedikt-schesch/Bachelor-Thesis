/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_slicetest_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    dace::perf::report.reset();

    {
        double *tmp = new double DACE_ALIGN(64)[((N - 1) * (N - 1))];
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i1 = 0; __i1 < (N - 1); __i1 += 1) {
                for (auto __i0 = 0; __i0 < (N - 1); __i0 += 1) {
                    {
                        double __in1 = A[(__i1 + ((N - 1) * (__i0 + 1)))];
                        double __in2 = B[((N * __i0) + __i1)];
                        double __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        tmp[((__i0 * (N - 1)) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_2.count());
        }
        {
            auto __dace_tbegin_0_0_10 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto j = 0; j < 4; j += 1) {
                {
                    for (auto i = 0; i < 4; i += 1) {
                        {
                            double t = tmp[((i * (N - 1)) + j)];
                            double c;

                            ///////////////////
                            // Tasklet code (slicetest_13)
                            c = t;
                            ///////////////////

                            C[((i * (N - 1)) + j)] = c;
                        }
                    }
                }
            }
            auto __dace_tend_0_0_10 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_10 = __dace_tend_0_0_10 - __dace_tbegin_0_0_10;
            dace::perf::report.add("timer_Map slicetest_12", __dace_tdiff_0_0_10.count());
        }
        delete[] tmp;
    }
    dace::perf::report.save(".dacecache/slicetest/perf");
}

DACE_EXPORTED void __program_slicetest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    __program_slicetest_internal(A, B, C, N);
}

DACE_EXPORTED int __dace_init_slicetest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_slicetest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
}

