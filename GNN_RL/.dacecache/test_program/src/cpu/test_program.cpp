/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_28(double* _in, double* _out, int M, int N, int O) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < N; _o0 += 1) {
                for (auto _o1 = 0; _o1 < M; _o1 += 1) {
                    {
                        double out;

                        ///////////////////
                        // Tasklet code (reduce_init)
                        out = 0;
                        ///////////////////

                        _out[((M * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < N; _o0 += 1) {
                for (auto _o1 = 0; _o1 < M; _o1 += 1) {
                    {
                        for (auto _i0 = 0; _i0 < O; _i0 += 1) {
                            {
                                double inp = _in[((((M * O) * _o0) + (O * _o1)) + _i0)];
                                double out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce(_out + ((M * _o0) + _o1), out);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_test_program_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ out1, double * __restrict__ out2, double * __restrict__ out3, int M, int N, int O)
{

    {
        double *tmp1 = new double DACE_ALIGN(64)[((M * N) * O)];
        double *t1 = new double DACE_ALIGN(64)[(M * N)];
        double *t2 = new double DACE_ALIGN(64)[(M * N)];
        double *tmp3 = new double DACE_ALIGN(64)[((M * N) * O)];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    {
                        double in1 = A[i];
                        double in2 = B[j];
                        double out;

                        ///////////////////
                        // Tasklet code (test_program_60)
                        out = ((in1 + in2) + 42);
                        ///////////////////

                        t2[((M * i) + j)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    {
                        double in1 = t2[((M * i) + j)];
                        double in2 = A[i];
                        double out;

                        ///////////////////
                        // Tasklet code (test_program_67)
                        out = (((in1 * in1) * in2) + in2);
                        ///////////////////

                        out1[((M * i) + j)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    for (auto k = 0; k < O; k += 1) {
                        double test_program_41_4_tp[1]  DACE_ALIGN(64);
                        {
                            double in1 = A[i];
                            double in2 = B[j];
                            double in3 = C[k];
                            double out;

                            ///////////////////
                            // Tasklet code (test_program_43)
                            out = ((in1 + in2) + in3);
                            ///////////////////

                            test_program_41_4_tp[0] = out;
                        }
                        {
                            double in1 = test_program_41_4_tp[0];
                            double out;

                            ///////////////////
                            // Tasklet code (test_program_51)
                            out = (in1 + 42);
                            ///////////////////

                            tmp1[((((M * O) * i) + (O * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        reduce_0_0_28(&tmp1[0], &t1[0], M, N, O);
        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    for (auto k = 0; k < O; k += 1) {
                        {
                            double in1 = t1[((M * i) + j)];
                            double in2 = t2[((M * i) + j)];
                            double in3 = C[k];
                            double out;

                            ///////////////////
                            // Tasklet code (test_program_75)
                            out = ((in1 + in2) + in3);
                            ///////////////////

                            tmp3[((((M * O) * i) + (O * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    for (auto k = 0; k < O; k += 1) {
                        {
                            double in1 = tmp3[((((M * O) * i) + (O * j)) + k)];
                            double in2 = tmp1[((((M * O) * i) + (O * j)) + k)];
                            double out;

                            ///////////////////
                            // Tasklet code (test_program_84)
                            out = (in1 + in2);
                            ///////////////////

                            out3[((((M * O) * i) + (O * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        {
            double in1 = tmp3[0];
            double out;

            ///////////////////
            // Tasklet code (fun)
            out = (in1 * 42);
            ///////////////////

            out2[0] = out;
        }
        delete[] tmp1;
        delete[] t1;
        delete[] t2;
        delete[] tmp3;
    }
}

DACE_EXPORTED void __program_test_program(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ out1, double * __restrict__ out2, double * __restrict__ out3, int M, int N, int O)
{
    __program_test_program_internal(A, B, C, out1, out2, out3, M, N, O);
}

DACE_EXPORTED int __dace_init_test_program(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ out1, double * __restrict__ out2, double * __restrict__ out3, int M, int N, int O)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_program(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ out1, double * __restrict__ out2, double * __restrict__ out3, int M, int N, int O)
{
}

