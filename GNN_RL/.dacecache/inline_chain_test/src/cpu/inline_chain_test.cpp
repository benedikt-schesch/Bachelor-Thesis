/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void inline_chain_test_11_4_0_1_2(double* __tmp_14_23_in_from_1_0, double* __tmp_15_23_out_of_1_1, double* __tmp_21_23_out_of_2_1) {

    {
        
        
        {
            for (auto j = 0; j < 20; j += 1) {
                {
                    double inA = __tmp_14_23_in_from_1_0[j];
                    double out;

                    ///////////////////
                    // Tasklet code (inline_chain_test_11_4_13)
                    out = (inA + 1);
                    ///////////////////

                    __tmp_15_23_out_of_1_1[j] = out;
                }
            }
        }
        {
            for (auto j = 0; j < 20; j += 1) {
                {
                    double intmp = __tmp_15_23_out_of_1_1[j];
                    double out;

                    ///////////////////
                    // Tasklet code (inline_chain_test_11_4_19)
                    out = (intmp + 1);
                    ///////////////////

                    __tmp_21_23_out_of_2_1[j] = out;
                }
            }
        }
    }
    
}

void __program_inline_chain_test_internal(double * __restrict__ A)
{
    dace::perf::report.reset();
    long long *__tmp1 = new long long DACE_ALIGN(64)[1];
    double *tmp = new double DACE_ALIGN(64)[400];

    {
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp1)
            out = 0;
            ///////////////////

            __tmp1[0] = out;
        }
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 20; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 20; __i1 += 1) {
                    {
                        long long __inp = __tmp1[0];
                        double __out;

                        ///////////////////
                        // Tasklet code (assign_9_4)
                        __out = __inp;
                        ///////////////////

                        tmp[((20 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map assign_9_4_map", __dace_tdiff_0_0_2.count());
        }
    }
    {
        
        
        {
            auto __dace_tbegin_0_1_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                inline_chain_test_11_4_0_1_2(&A[(20 * i)], &tmp[(20 * i)], &A[(20 * i)]);
            }
            auto __dace_tend_0_1_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_0 = __dace_tend_0_1_0 - __dace_tbegin_0_1_0;
            dace::perf::report.add("timer_Map inline_chain_test_11", __dace_tdiff_0_1_0.count());
        }
    }
    delete[] __tmp1;
    delete[] tmp;
    dace::perf::report.save(".dacecache/inline_chain_test/perf");
}

DACE_EXPORTED void __program_inline_chain_test(double * __restrict__ A)
{
    __program_inline_chain_test_internal(A);
}

DACE_EXPORTED int __dace_init_inline_chain_test(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_inline_chain_test(double * __restrict__ A)
{
}

