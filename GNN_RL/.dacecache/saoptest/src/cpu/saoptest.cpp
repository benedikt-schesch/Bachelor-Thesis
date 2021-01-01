/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_saoptest_internal(double * __restrict__ A, double * __restrict__ B, double alpha)
{
    dace::perf::report.reset();
    long long *__tmp1 = new long long DACE_ALIGN(64)[1];

    {
        double *__tmp0 = new double DACE_ALIGN(64)[25];
        double *tmp = new double DACE_ALIGN(64)[25];
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp1)
            out = 5;
            ///////////////////

            __tmp1[0] = out;
        }
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                    {
                        double __in2 = A[((5 * __i0) + __i1)];
                        double __in1 = alpha;
                        double __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        __tmp0[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_2.count());
        }
        {
            auto __dace_tbegin_0_0_8 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                    {
                        double __in1 = __tmp0[((5 * __i0) + __i1)];
                        long long __in2 = __tmp1[0];
                        double __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        tmp[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_8 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_8 = __dace_tend_0_0_8 - __dace_tbegin_0_0_8;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_8.count());
        }
        {
            auto __dace_tbegin_0_0_12 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 5; i += 1) {
                for (auto j = 0; j < 5; j += 1) {
                    {
                        double t = tmp[((5 * i) + j)];
                        double c;

                        ///////////////////
                        // Tasklet code (saoptest_11)
                        c = t;
                        ///////////////////

                        B[((5 * i) + j)] = c;
                    }
                }
            }
            auto __dace_tend_0_0_12 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_12 = __dace_tend_0_0_12 - __dace_tbegin_0_0_12;
            dace::perf::report.add("timer_Map saoptest_10", __dace_tdiff_0_0_12.count());
        }
        delete[] __tmp0;
        delete[] tmp;
    }
    delete[] __tmp1;
    dace::perf::report.save(".dacecache/saoptest/perf");
}

DACE_EXPORTED void __program_saoptest(double * __restrict__ A, double * __restrict__ B, double alpha)
{
    __program_saoptest_internal(A, B, alpha);
}

DACE_EXPORTED int __dace_init_saoptest(double * __restrict__ A, double * __restrict__ B, double alpha)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_saoptest(double * __restrict__ A, double * __restrict__ B, double alpha)
{
}

