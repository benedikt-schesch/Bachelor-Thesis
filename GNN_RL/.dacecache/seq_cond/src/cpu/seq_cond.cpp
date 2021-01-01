/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_seq_cond_internal(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    long long n;

    for (n = 0; (n < N); n = (n + 1)) {
        if ((n < (N - 1))) {
            {
                
                

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Accumulate(
                sigmaRSE + ((BS * BS) * n), HE + ((BS * BS) * n), [] (const dace::complex128& x, const dace::complex128& y) { return (x - y); }, (BS * BS), 1);
            }
        } else {
            {
                dace::complex128 *__tmp2 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = sigmaRSE[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_USub_)
                                __out = (- __in1);
                                ///////////////////

                                __tmp2[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp2, HE + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp2;
            }
        }
        if ((n > 0)) {
            {
                
                

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Accumulate(
                sigmaRSF + ((BS * BS) * n), HF + ((BS * BS) * n), [] (const dace::complex128& x, const dace::complex128& y) { return (x - y); }, (BS * BS), 1);
            }
        } else {
            {
                dace::complex128 *__tmp5 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = sigmaRSF[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_USub_)
                                __out = (- __in1);
                                ///////////////////

                                __tmp5[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp5, HF + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp5;
            }
        }
        {
            dace::complex128 *__tmp8 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            
            
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = HD[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                            dace::complex128 __in2 = sigmaRSD[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp8[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp8, HD + ((BS * BS) * n), (BS * BS), 1);
            delete[] __tmp8;
        }
    }
}

DACE_EXPORTED void __program_seq_cond(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    __program_seq_cond_internal(HD, HE, HF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
}

DACE_EXPORTED int __dace_init_seq_cond(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_seq_cond(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
}

