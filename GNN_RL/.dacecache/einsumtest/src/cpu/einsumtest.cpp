/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void einsum_gemm_sdfg_1_0_3(double* _a, double* _b, double* _c, int K, int M, int N) {

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

                        _c[(_o0 + _o1)] = out;
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
                    for (auto __i2 = 0; __i2 < K; __i2 += 1) {
                        {
                            double __a = _a[((10 * __i0) + __i2)];
                            double __b = _b[(__i1 + __i2)];
                            double __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_c + (__i0 + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void einsum_0_0_18(double* X, double* Y, double* Z, long long BATCH, int K, int M, int N, long long sAB, long long sAK, long long sAM, long long sBB, long long sBK, long long sBN, long long sCB, long long sCM, long long sCN) {

    {
        
        
        einsum_gemm_sdfg_1_0_3(&X[0], &Y[0], &Z[0], K, M, N);
    }
    
}

void __program_einsumtest_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, double * __restrict__ E, double * __restrict__ __return)
{
    double *__tmp0 = new double DACE_ALIGN(64)[1000];
    double *__tmp1 = new double DACE_ALIGN(64)[10];
    double *__tmp2 = new double DACE_ALIGN(64)[10];

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < 10; i += 1) {
                        for (auto k = 0; k < 10; k += 1) {
                            for (auto b = 0; b < 10; b += 1) {
                                {
                                    double out___tmp0;

                                    ///////////////////
                                    // Tasklet code (einsum_reset)
                                    out___tmp0 = 0;
                                    ///////////////////

                                    __tmp0[((b + (100 * i)) + (10 * k))] = out___tmp0;
                                }
                            }
                        }
                    }
                }
            } // End omp section
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto a = 0; a < 10; a += 1) {
                        {
                            double out___tmp1;

                            ///////////////////
                            // Tasklet code (einsum_reset)
                            out___tmp1 = 0;
                            ///////////////////

                            __tmp1[a] = out___tmp1;
                        }
                    }
                }
            } // End omp section
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto a = 0; a < 10; a += 1) {
                        {
                            double out___tmp2;

                            ///////////////////
                            // Tasklet code (einsum_reset)
                            out___tmp2 = 0;
                            ///////////////////

                            __tmp2[a] = out___tmp2;
                        }
                    }
                }
            } // End omp section
        } // End omp sections
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto a = 0; a < 10; a += 1) {
                for (auto j = 0; j < 10; j += 1) {
                    for (auto c = 0; c < 10; c += 1) {
                        {
                            double inp_B = B[(((1010 * a) + (100 * c)) + j)];
                            double inp_D = D[(((1010 * a) + c) + (100 * j))];
                            double out___tmp2;

                            ///////////////////
                            // Tasklet code (einsum)
                            out___tmp2 = (inp_D * inp_B);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(__tmp2 + a, out___tmp2);
                        }
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto k = 0; k < 10; k += 1) {
                    for (auto b = 0; b < 10; b += 1) {
                        for (auto d = 0; d < 10; d += 1) {
                            {
                                double inp_A = A[((((1000 * b) + (100 * d)) + (10 * i)) + k)];
                                double inp_E = E[((((10 * b) + d) + (1000 * i)) + (100 * k))];
                                double out___tmp0;

                                ///////////////////
                                // Tasklet code (einsum)
                                out___tmp0 = (inp_E * inp_A);
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(__tmp0 + ((b + (100 * i)) + (10 * k)), out___tmp0);
                            }
                        }
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto k = 0; k < 10; k += 1) {
                    for (auto b = 0; b < 10; b += 1) {
                        for (auto a = 0; a < 10; a += 1) {
                            {
                                double inp_C = C[((((10 * a) + b) + (1000 * i)) + (100 * k))];
                                double inp___tmp0 = __tmp0[((b + (100 * i)) + (10 * k))];
                                double out___tmp1;

                                ///////////////////
                                // Tasklet code (einsum)
                                out___tmp1 = (inp___tmp0 * inp_C);
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(__tmp1 + a, out___tmp1);
                            }
                        }
                    }
                }
            }
        }
        einsum_0_0_18(&__tmp2[0], &__tmp1[0], &__return[0], 1, 10, 1, 1, 10, 1, 10, 10, 1, 1, 1, 1, 1);
    }
    delete[] __tmp0;
    delete[] __tmp1;
    delete[] __tmp2;
}

DACE_EXPORTED void __program_einsumtest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, double * __restrict__ E, double * __restrict__ __return)
{
    __program_einsumtest_internal(A, B, C, D, E, __return);
}

DACE_EXPORTED int __dace_init_einsumtest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, double * __restrict__ E, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_einsumtest(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, double * __restrict__ D, double * __restrict__ E, double * __restrict__ __return)
{
}

