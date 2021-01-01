/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_multiret_internal(double * __restrict__ A, double * __restrict__ __return_0, double * __restrict__ __return_1, double * __restrict__ __return_2)
{
    dace::perf::report.reset();
    long long *__tmp0 = new long long DACE_ALIGN(64)[1];
    long long *__tmp2 = new long long DACE_ALIGN(64)[1];

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {

                dace::CopyND<double, 1, false, 20>::template ConstDst<1>::Copy(
                A, __return_2, 1);
            } // End omp section
            #pragma omp section
            {
                {
                    long long out;

                    ///////////////////
                    // Tasklet code (init___tmp0)
                    out = 3;
                    ///////////////////

                    __tmp0[0] = out;
                }

                dace::CopyND<double, 1, false, 20>::template ConstDst<1>::Copy(
                A, __return_2, 1);
                {
                    auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                        {
                            double __in1 = A[__i0];
                            long long __in2 = __tmp0[0];
                            double __out;

                            ///////////////////
                            // Tasklet code (_Mult_)
                            __out = (__in1 * __in2);
                            ///////////////////

                            __return_0[__i0] = __out;
                        }
                    }
                    auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
                    dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_4.count());
                }
            } // End omp section
            #pragma omp section
            {
                {
                    long long out;

                    ///////////////////
                    // Tasklet code (init___tmp2)
                    out = 4;
                    ///////////////////

                    __tmp2[0] = out;
                }

                dace::CopyND<double, 1, false, 20>::template ConstDst<1>::Copy(
                A, __return_2, 1);
                {
                    auto __dace_tbegin_0_0_9 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                        {
                            double __in1 = A[__i0];
                            long long __in2 = __tmp2[0];
                            double __out;

                            ///////////////////
                            // Tasklet code (_Mult_)
                            __out = (__in1 * __in2);
                            ///////////////////

                            __return_1[__i0] = __out;
                        }
                    }
                    auto __dace_tend_0_0_9 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_9 = __dace_tend_0_0_9 - __dace_tbegin_0_0_9;
                    dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_9.count());
                }
            } // End omp section
        } // End omp sections
    }
    delete[] __tmp0;
    delete[] __tmp2;
    dace::perf::report.save(".dacecache/multiret/perf");
}

DACE_EXPORTED void __program_multiret(double * __restrict__ A, double * __restrict__ __return_0, double * __restrict__ __return_1, double * __restrict__ __return_2)
{
    __program_multiret_internal(A, __return_0, __return_1, __return_2);
}

DACE_EXPORTED int __dace_init_multiret(double * __restrict__ A, double * __restrict__ __return_0, double * __restrict__ __return_1, double * __restrict__ __return_2)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_multiret(double * __restrict__ A, double * __restrict__ __return_0, double * __restrict__ __return_1, double * __restrict__ __return_2)
{
}

