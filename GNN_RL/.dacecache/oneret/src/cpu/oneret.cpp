/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_oneret_internal(double * __restrict__ A, double * __restrict__ __return)
{
    dace::perf::report.reset();
    long long *__tmp0 = new long long DACE_ALIGN(64)[1];

    {
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 2;
            ///////////////////

            __tmp0[0] = out;
        }
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
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

                    __return[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_2.count());
        }
    }
    delete[] __tmp0;
    dace::perf::report.save(".dacecache/oneret/perf");
}

DACE_EXPORTED void __program_oneret(double * __restrict__ A, double * __restrict__ __return)
{
    __program_oneret_internal(A, __return);
}

DACE_EXPORTED int __dace_init_oneret(double * __restrict__ A, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_oneret(double * __restrict__ A, double * __restrict__ __return)
{
}

