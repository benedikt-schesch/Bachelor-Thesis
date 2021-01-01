/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_optest_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
    dace::perf::report.reset();

    {
        double *__tmp0 = new double DACE_ALIGN(64)[25];
        double *tmp = new double DACE_ALIGN(64)[25];
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    {
                        double __in1 = A[((5 * __i0) + __i1)];
                        double __out;

                        ///////////////////
                        // Tasklet code (_USub_)
                        __out = (- __in1);
                        ///////////////////

                        __tmp0[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map _USub__map", __dace_tdiff_0_0_0.count());
        }
        {
            auto __dace_tbegin_0_0_5 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 5; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    {
                        double __in2 = B[((5 * __i0) + __i1)];
                        double __in1 = __tmp0[((5 * __i0) + __i1)];
                        double __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        tmp[((5 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_5 = __dace_tend_0_0_5 - __dace_tbegin_0_0_5;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_5.count());
        }
        {
            auto __dace_tbegin_0_0_10 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 5; i += 1) {
                for (auto j = 0; j < 5; j += 1) {
                    {
                        double t = tmp[((5 * i) + j)];
                        double c;

                        ///////////////////
                        // Tasklet code (optest_11)
                        c = t;
                        ///////////////////

                        C[((5 * i) + j)] = c;
                    }
                }
            }
            auto __dace_tend_0_0_10 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_10 = __dace_tend_0_0_10 - __dace_tbegin_0_0_10;
            dace::perf::report.add("timer_Map optest_10", __dace_tdiff_0_0_10.count());
        }
        delete[] __tmp0;
        delete[] tmp;
    }
    dace::perf::report.save(".dacecache/optest/perf");
}

DACE_EXPORTED void __program_optest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
    __program_optest_internal(A, B, C);
}

DACE_EXPORTED int __dace_init_optest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_optest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C)
{
}

