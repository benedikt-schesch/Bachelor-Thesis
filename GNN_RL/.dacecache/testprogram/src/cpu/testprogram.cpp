/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_testprogram_internal(double * __restrict__ A, double * __restrict__ __return)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                {
                    double __in1 = A[__i0];
                    double __in2 = A[__i0];
                    double __out;

                    ///////////////////
                    // Tasklet code (_Add_)
                    __out = (__in1 + __in2);
                    ///////////////////

                    __return[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map _Add__map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/testprogram/perf");
}

DACE_EXPORTED void __program_testprogram(double * __restrict__ A, double * __restrict__ __return)
{
    __program_testprogram_internal(A, __return);
}

DACE_EXPORTED int __dace_init_testprogram(double * __restrict__ A, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_testprogram(double * __restrict__ A, double * __restrict__ __return)
{
}

