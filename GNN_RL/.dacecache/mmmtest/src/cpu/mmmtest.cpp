/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_0_0_3(double* _a, double* _b, double* _c, int B, int K, int M, int N) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < B; _o0 += 1) {
                for (auto _o1 = 0; _o1 < M; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < N; _o2 += 1) {
                        {
                            double out;

                            ///////////////////
                            // Tasklet code (batched_matmul_init)
                            out = 0;
                            ///////////////////

                            _c[((((M * N) * _o0) + (N * _o1)) + _o2)] = out;
                        }
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < B; __i0 += 1) {
                for (auto __i1 = 0; __i1 < M; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < N; __i2 += 1) {
                        for (auto __i3 = 0; __i3 < K; __i3 += 1) {
                            {
                                double __a = _a[((K * __i1) + __i3)];
                                double __b = _b[((((K * N) * __i0) + (N * __i3)) + __i2)];
                                double __c;

                                ///////////////////
                                // Tasklet code (_BatchedBatchedMatMult_)
                                __c = (__a * __b);
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_c + ((((M * N) * __i0) + (N * __i1)) + __i2), __c);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_mmmtest_internal(double * __restrict__ __return, double * __restrict__ a, double * __restrict__ b, int B, int K, int M, int N)
{

    {
        
        
        _MatMult__sdfg_0_0_3(&a[0], &b[0], &__return[0], B, K, M, N);
    }
}

DACE_EXPORTED void __program_mmmtest(double * __restrict__ __return, double * __restrict__ a, double * __restrict__ b, int B, int K, int M, int N)
{
    __program_mmmtest_internal(__return, a, b, B, K, M, N);
}

DACE_EXPORTED int __dace_init_mmmtest(double * __restrict__ __return, double * __restrict__ a, double * __restrict__ b, int B, int K, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mmmtest(double * __restrict__ __return, double * __restrict__ a, double * __restrict__ b, int B, int K, int M, int N)
{
}

