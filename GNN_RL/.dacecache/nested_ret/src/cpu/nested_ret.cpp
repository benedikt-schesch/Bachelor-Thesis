/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_nested_ret_internal(double * __restrict__ A, double * __restrict__ __return)
{
    dace::perf::report.reset();
    long long *__tmp2 = new long long DACE_ALIGN(64)[1];
    long long *oneret___tmp0 = new long long DACE_ALIGN(64)[1];

    {
        double *oneret_ret_0 = new double DACE_ALIGN(64)[20];
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp2)
            out = 1;
            ///////////////////

            __tmp2[0] = out;
        }
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 2;
            ///////////////////

            oneret___tmp0[0] = out;
        }
        {
            auto __dace_tbegin_0_0_10 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                {
                    double __in1 = A[__i0];
                    long long __in2 = oneret___tmp0[0];
                    double __out;

                    ///////////////////
                    // Tasklet code (_Mult_)
                    __out = (__in1 * __in2);
                    ///////////////////

                    oneret_ret_0[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_10 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_10 = __dace_tend_0_0_10 - __dace_tbegin_0_0_10;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_10.count());
        }
        {
            auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                {
                    long long __in2 = __tmp2[0];
                    double __in1 = oneret_ret_0[__i0];
                    double __out;

                    ///////////////////
                    // Tasklet code (_Add_)
                    __out = (__in1 + __in2);
                    ///////////////////

                    __return[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
            dace::perf::report.add("timer_Map _Add__map", __dace_tdiff_0_0_4.count());
        }
        delete[] oneret_ret_0;
    }
    delete[] __tmp2;
    delete[] oneret___tmp0;
    dace::perf::report.save(".dacecache/nested_ret/perf");
}

DACE_EXPORTED void __program_nested_ret(double * __restrict__ A, double * __restrict__ __return)
{
    __program_nested_ret_internal(A, __return);
}

DACE_EXPORTED int __dace_init_nested_ret(double * __restrict__ A, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_ret(double * __restrict__ A, double * __restrict__ __return)
{
}

