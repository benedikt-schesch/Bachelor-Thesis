/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_highdim_internal(unsigned long long * __restrict__ A, unsigned long long * __restrict__ B, int K, int L, int M, int N, int U, int W, int X, int Y, int Z)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 5; i < (N - 5); i += 1) {
                for (auto j = 0; j < M; j += 1) {
                    for (auto k = 7; k < (K - 1); k += 1) {
                        for (auto l = 0; l < L; l += 1) {
                            {
                                for (auto a = 0; a < X; a += 1) {
                                    for (auto b = 0; b < Y; b += 1) {
                                        for (auto c = 1; c < Z; c += 1) {
                                            for (auto d = 2; d < (W - 2); d += 1) {
                                                for (auto e = 0; e < U; e += 1) {
                                                    {
                                                        unsigned long long input = A[((((((((((((((((K * L) * M) * U) * W) * X) * Y) * Z) * i) + (((((((K * L) * U) * W) * X) * Y) * Z) * j)) + ((((((L * U) * W) * X) * Y) * Z) * k)) + (((((U * W) * X) * Y) * Z) * l)) + ((((U * W) * Y) * Z) * a)) + (((U * W) * Z) * b)) + ((U * W) * c)) + (U * d)) + e)];
                                                        unsigned long long output;

                                                        ///////////////////
                                                        // Tasklet code (block)
                                                        output = input;
                                                        ///////////////////

                                                        dace::wcr_fixed<dace::ReductionType::Sum, unsigned long long>::reduce(B + ((((((K * L) * M) * i) + ((K * L) * j)) + (L * k)) + l), output);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_highdim(unsigned long long * __restrict__ A, unsigned long long * __restrict__ B, int K, int L, int M, int N, int U, int W, int X, int Y, int Z)
{
    __program_highdim_internal(A, B, K, L, M, N, U, W, X, Y, Z);
}

DACE_EXPORTED int __dace_init_highdim(unsigned long long * __restrict__ A, unsigned long long * __restrict__ B, int K, int L, int M, int N, int U, int W, int X, int Y, int Z)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_highdim(unsigned long long * __restrict__ A, unsigned long long * __restrict__ B, int K, int L, int M, int N, int U, int W, int X, int Y, int Z)
{
}

