/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_13(double* _in, double* _out, int M) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
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
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
                for (auto _o1 = 0; _o1 < M; _o1 += 1) {
                    {
                        for (auto _i0 = 0; _i0 < M; _i0 += 1) {
                            {
                                double inp = _in[((((M * M) * _o0) + (M * _o1)) + _i0)];
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

inline void _MatMult__sdfg_1_0_0_14(double* _a, double* _b, double* _c, int M) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
                for (auto _o1 = 0; _o1 < M; _o1 += 1) {
                    {
                        double out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((M * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                for (auto __i1 = 0; __i1 < M; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < M; __i2 += 1) {
                        {
                            double __a = _a[((M * __i0) + __i2)];
                            double __b = _b[((M * __i2) + __i1)];
                            double __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_c + ((M * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_4_0_0_17(double* _a, double* _b, double* _c, int M, int N) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < M; _o0 += 1) {
                for (auto _o1 = 0; _o1 < N; _o1 += 1) {
                    {
                        double out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((N * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                for (auto __i1 = 0; __i1 < N; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < M; __i2 += 1) {
                        {
                            double __a = _a[((M * __i0) + __i2)];
                            double __b = _b[((N * __i2) + __i1)];
                            double __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_c + ((N * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_operation_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, int M, int N)
{

    {
        double *tmp = new double DACE_ALIGN(64)[(M * M * M)];
        double *transient_reuse = new double DACE_ALIGN(64)[(M * M)];
        double *__tmp2 = new double DACE_ALIGN(64)[(M * M)];
        double *__tmp3 = new double DACE_ALIGN(64)[(M * M)];
        double *__tmp5 = new double DACE_ALIGN(64)[(M * N)];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < M; i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    for (auto k = 0; k < M; k += 1) {
                        {
                            double in_A = A[((M * i) + k)];
                            double in_B = B[((M * k) + j)];
                            double out;

                            ///////////////////
                            // Tasklet code (multiplication)
                            out = (in_A * in_B);
                            ///////////////////

                            tmp[((((M * M) * i) + (M * j)) + k)] = out;
                        }
                    }
                }
            }
        }
        reduce_0_0_13(&tmp[0], &transient_reuse[0], M);
        _MatMult__sdfg_1_0_0_14(&A[0], &transient_reuse[0], &__tmp2[0], M);
        _MatMult__sdfg_1_0_0_14(&A[0], &B[0], &__tmp3[0], M);
        _MatMult__sdfg_1_0_0_14(&__tmp2[0], &__tmp3[0], &transient_reuse[0], M);
        _MatMult__sdfg_4_0_0_17(&B[0], &D[0], &__tmp5[0], M, N);
        _MatMult__sdfg_4_0_0_17(&transient_reuse[0], &__tmp5[0], &C[0], M, N);
        delete[] tmp;
        delete[] transient_reuse;
        delete[] __tmp2;
        delete[] __tmp3;
        delete[] __tmp5;
    }
}

DACE_EXPORTED void __program_operation(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, int M, int N)
{
    __program_operation_internal(A, B, C, D, M, N);
}

DACE_EXPORTED int __dace_init_operation(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_operation(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, int M, int N)
{
}

