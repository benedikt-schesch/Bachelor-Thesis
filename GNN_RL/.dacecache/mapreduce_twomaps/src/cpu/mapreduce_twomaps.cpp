/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_mapreduce_twomaps_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto k = 0; k < K; k += 1) {
                for (auto j = 0; j < N; j += 1) {
                    for (auto i = 0; i < M; i += 1) {
                        double __s0_n6out_n1IN_1;
                        {
                            double in_A = A[((K * i) + k)];
                            double in_B = B[((N * k) + j)];
                            double out;

                            ///////////////////
                            // Tasklet code (multiplication)
                            out = (in_A * in_B);
                            ///////////////////

                            __s0_n6out_n1IN_1 = out;
                        }
                        {
                            const double& ti = __s0_n6out_n1IN_1;
                            double out_C;

                            ///////////////////
                            // Tasklet code (summation_inner)
                            out_C = ti;
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(C + ((N * i) + j), out_C);
                        }
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_mapreduce_twomaps(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{
    __program_mapreduce_twomaps_internal(A, B, C, K, M, N);
}

DACE_EXPORTED int __dace_init_mapreduce_twomaps(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mapreduce_twomaps(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int K, int M, int N)
{
}

