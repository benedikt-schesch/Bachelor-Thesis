/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void reduce_2_0_0_17(double* _in, double* _out, int M, int N) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = (- 1.7976931348623157e+308);
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    for (auto _i0 = 0; _i0 < M; _i0 += 1) {
                        {
                            double inp = _in[((N * _i0) + _o0)];
                            double out;

                            ///////////////////
                            // Tasklet code (identity)
                            out = inp;
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Max, double>::reduce(_out + _o0, out);
                        }
                    }
                }
            }
        }
    }
    
}

#include <chrono>
inline void reduce_3_0_0_18(double* _in, double* _out, int M, int N) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    for (auto _i0 = 0; _i0 < M; _i0 += 1) {
                        {
                            double inp = _in[((N * _i0) + _o0)];
                            double out;

                            ///////////////////
                            // Tasklet code (identity)
                            out = inp;
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce(_out + _o0, out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_test_program2_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N)
{
    dace::perf::report.reset();

    {
        double *tmp = new double DACE_ALIGN(64)[(M * N)];
        
        
        {
            auto __dace_tbegin_0_0_9 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < N; _o0 += 1) {
                double reduce_trans__out[1]  DACE_ALIGN(64);
                reduce_2_0_0_17(&B[_o0], &reduce_trans__out[0], M, N);
                {
                    double reduction_in = reduce_trans__out[0];
                    double array_in = C[_o0];
                    double out;

                    ///////////////////
                    // Tasklet code (reduction_transient_update)
                    out = max(reduction_in, array_in);
                    ///////////////////

                    C[_o0] = out;
                }
            }
            auto __dace_tend_0_0_9 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_9 = __dace_tend_0_0_9 - __dace_tbegin_0_0_9;
            dace::perf::report.add("timer_Map reduce_output", __dace_tdiff_0_0_9.count());
        }
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < M; i += 1) {
                for (auto j = 0; j < N; j += 1) {
                    {
                        double in1 = C[j];
                        double in2 = A[((N * i) + j)];
                        double out1;

                        ///////////////////
                        // Tasklet code (test_program2_35)
                        out1 = (in1 * in2);
                        ///////////////////

                        tmp[((N * i) + j)] = out1;
                    }
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map test_program2_34", __dace_tdiff_0_0_2.count());
        }
        {
            auto __dace_tbegin_0_0_13 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < N; _o0 += 1) {
                double reduce_1_trans__out[1]  DACE_ALIGN(64);
                reduce_3_0_0_18(&tmp[_o0], &reduce_1_trans__out[0], M, N);
                {
                    double reduction_in = reduce_1_trans__out[0];
                    double array_in = C[_o0];
                    double out;

                    ///////////////////
                    // Tasklet code (reduction_transient_update)
                    out = (reduction_in + array_in);
                    ///////////////////

                    C[_o0] = out;
                }
            }
            auto __dace_tend_0_0_13 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_13 = __dace_tend_0_0_13 - __dace_tbegin_0_0_13;
            dace::perf::report.add("timer_Map reduce_output", __dace_tdiff_0_0_13.count());
        }
        delete[] tmp;
    }
    dace::perf::report.save(".dacecache/test_program2/perf");
}

DACE_EXPORTED void __program_test_program2(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N)
{
    __program_test_program2_internal(A, B, C, M, N);
}

DACE_EXPORTED int __dace_init_test_program2(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_program2(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int M, int N)
{
}

