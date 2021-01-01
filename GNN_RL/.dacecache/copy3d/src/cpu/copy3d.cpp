/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_copy3d_internal(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < M; i += 1) {
                {
                    for (auto j = 0; j < N; j += 1) {
                        for (auto k = 0; k < K; k += 1) {
                            {
                                float a = A[((((K * N) * i) + (K * j)) + k)];
                                float b;

                                ///////////////////
                                // Tasklet code (copy3d_10_4_12)
                                b = a;
                                ///////////////////

                                B[((((K * N) * i) + (K * j)) + k)] = b;
                            }
                        }
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_copy3d(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
    __program_copy3d_internal(A, B, K, M, N);
}

DACE_EXPORTED int __dace_init_copy3d(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_copy3d(float * __restrict__ A, float * __restrict__ B, int K, int M, int N)
{
}

