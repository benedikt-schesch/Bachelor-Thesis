/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void ttest_17_4_18_8_19_12_0_0_16(float* __tmp_20_29_r, int* __tmp_20_16_w, float* __tmp_21_16_w) {
    double __tmp5[1]  DACE_ALIGN(64);

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (init___tmp5)
                    out = 1.0;
                    ///////////////////

                    __tmp5[0] = out;
                }
                {
                    double __inp = __tmp5[0];
                    float __out;

                    ///////////////////
                    // Tasklet code (assign_21_16)
                    __out = __inp;
                    ///////////////////

                    __tmp_21_16_w[0] = __out;
                }
            } // End omp section
            #pragma omp section
            {
                {
                    float __inp = __tmp_20_29_r[0];
                    int __out;

                    ///////////////////
                    // Tasklet code (assign_20_16)
                    __out = __inp;
                    ///////////////////

                    __tmp_20_16_w[0] = __out;
                }
            } // End omp section
        } // End omp sections
    }
    {
        
        
        {
            float __inp = __tmp_21_16_w[0];
            int __out;

            ///////////////////
            // Tasklet code (assign_22_16)
            __out = __inp;
            ///////////////////

            __tmp_20_16_w[0] = __out;
        }
    }
    
}

void __program_ttest_internal(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
    long long *__tmp2 = new long long DACE_ALIGN(64)[1];
    float *t = new float DACE_ALIGN(64)[((K * M) * N)];
    float *__tmp3 = new float DACE_ALIGN(64)[((K * M) * N)];

    {
        int *s = new int DACE_ALIGN(64)[((K * M) * N)];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < M; i += 1) {
                        {
                            for (auto j = 0; j < N; j += 1) {
                                {
                                    for (auto k = 0; k < K; k += 1) {
                                        ttest_17_4_18_8_19_12_0_0_16(&t[((((K * N) * i) + (K * j)) + k)], &s[((((M * N) * k) + (M * j)) + i)], &t[((((K * N) * i) + (K * j)) + k)]);
                                    }
                                }
                            }
                        }
                    }
                }
            } // End omp section
            #pragma omp section
            {
                {
                    long long out;

                    ///////////////////
                    // Tasklet code (init___tmp2)
                    out = 5;
                    ///////////////////

                    __tmp2[0] = out;
                }
                {
                    #pragma omp parallel for
                    for (auto __i2 = 0; __i2 < K; __i2 += 1) {
                        for (auto __i1 = 0; __i1 < N; __i1 += 1) {
                            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                                {
                                    float __in2 = A[((((K * N) * __i0) + (K * __i1)) + __i2)];
                                    long long __in1 = __tmp2[0];
                                    float __out;

                                    ///////////////////
                                    // Tasklet code (_Mult_)
                                    __out = (__in1 * __in2);
                                    ///////////////////

                                    __tmp3[((((K * N) * __i0) + (K * __i1)) + __i2)] = __out;
                                }
                            }
                        }
                    }
                }
            } // End omp section
        } // End omp sections
        delete[] s;
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                for (auto __i1 = 0; __i1 < N; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < K; __i2 += 1) {
                        {
                            float __in1 = t[((((K * N) * __i0) + (K * __i1)) + __i2)];
                            float __in2 = __tmp3[((((K * N) * __i0) + (K * __i1)) + __i2)];
                            float __out;

                            ///////////////////
                            // Tasklet code (augassign_24_4)
                            __out = (__in1 + __in2);
                            ///////////////////

                            t[((((K * N) * __i0) + (K * __i1)) + __i2)] = __out;
                        }
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                for (auto __i1 = 0; __i1 < N; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < K; __i2 += 1) {
                        {
                            float __in1 = B[((((K * N) * __i0) + (K * __i1)) + __i2)];
                            float __in2 = t[((((K * N) * __i0) + (K * __i1)) + __i2)];
                            float __out;

                            ///////////////////
                            // Tasklet code (augassign_25_4)
                            __out = (__in1 - __in2);
                            ///////////////////

                            B[((((K * N) * __i0) + (K * __i1)) + __i2)] = __out;
                        }
                    }
                }
            }
        }
    }
    delete[] __tmp2;
    delete[] t;
    delete[] __tmp3;
}

DACE_EXPORTED void __program_ttest(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
    __program_ttest_internal(A, B, K, M, N);
}

DACE_EXPORTED int __dace_init_ttest(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_ttest(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
}

