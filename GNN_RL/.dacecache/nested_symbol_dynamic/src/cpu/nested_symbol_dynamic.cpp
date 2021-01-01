/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_nested_symbol_dynamic_internal(double * __restrict__ A, int N)
{
    dace::perf::report.reset();
    int i;

    for (i = 0; (i < 5); i = (i + 1)) {
        {
            double *__tmp1 = new double DACE_ALIGN(64)[i];
            
            
            double __tmp3;
            {
                double factor;

                ///////////////////
                // Tasklet code (scalar)
                factor = i;
                ///////////////////

                __tmp3 = factor;
            }
            {
                auto __dace_tbegin_0_1_4 = std::chrono::high_resolution_clock::now();
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < i; __i0 += 1) {
                    {
                        double __in1 = A[__i0];
                        const double& __in2 = __tmp3;
                        double __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        __tmp1[__i0] = __out;
                    }
                }
                auto __dace_tend_0_1_4 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> __dace_tdiff_0_1_4 = __dace_tend_0_1_4 - __dace_tbegin_0_1_4;
                dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_1_4.count());
            }

            dace::CopyNDDynamic<double, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp1, A, i, 1);
            delete[] __tmp1;
        }
    }
    dace::perf::report.save(".dacecache/nested_symbol_dynamic/perf");
}

DACE_EXPORTED void __program_nested_symbol_dynamic(double * __restrict__ A, int N)
{
    __program_nested_symbol_dynamic_internal(A, N);
}

DACE_EXPORTED int __dace_init_nested_symbol_dynamic(double * __restrict__ A, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_symbol_dynamic(double * __restrict__ A, int N)
{
}

