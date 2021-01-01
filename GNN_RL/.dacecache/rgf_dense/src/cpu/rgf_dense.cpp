/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_1_0_9_29(dace::complex128* _a, dace::complex128* _b, dace::complex128* _c, int BS) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < BS; _o0 += 1) {
                for (auto _o1 = 0; _o1 < BS; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((BS * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < BS; __i2 += 1) {
                        {
                            dace::complex128 __a = _a[((BS * __i0) + __i2)];
                            dace::complex128 __b = _b[((BS * __i2) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce_atomic(_c + ((BS * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_rgf_dense_internal(dace::complex128 * __restrict__ GG, dace::complex128 * __restrict__ GL, dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ dTGL, double * __restrict__ fl, double * __restrict__ fr, dace::complex128 * __restrict__ gammaleft, dace::complex128 * __restrict__ gammaright, dace::complex128 * __restrict__ sigRl, dace::complex128 * __restrict__ sigRr, dace::complex128 * __restrict__ sigmaGSD, dace::complex128 * __restrict__ sigmaGSE, dace::complex128 * __restrict__ sigmaGSF, dace::complex128 * __restrict__ sigmaLSD, dace::complex128 * __restrict__ sigmaLSE, dace::complex128 * __restrict__ sigmaLSF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    dace::complex128 *__tmp9 = new dace::complex128 DACE_ALIGN(64)[1];
    long long *__tmp14 = new long long DACE_ALIGN(64)[1];
    dace::complex128 *sigLl = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *sigLr = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *sigGr = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *sigGl = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *gR = new dace::complex128 DACE_ALIGN(64)[((BS * BS) * N)];
    dace::complex128 *her_gR = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *gL = new dace::complex128 DACE_ALIGN(64)[((BS * BS) * N)];
    dace::complex128 *gG = new dace::complex128 DACE_ALIGN(64)[((BS * BS) * N)];
    dace::complex128 *M = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *her_M1 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *__tmp76 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *GR = new dace::complex128 DACE_ALIGN(64)[((BS * BS) * N)];
    dace::complex128 *her_GR = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *__tmp120 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *GLnd = new dace::complex128 DACE_ALIGN(64)[((BS * BS) * N)];
    dace::complex128 *M1 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *M2 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *her_M2 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    dace::complex128 *__tmp202 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
    long long n;

    {
        dace::complex128 *__tmp10 = new dace::complex128 DACE_ALIGN(64)[1];
        dace::complex128 *__tmp12 = new dace::complex128 DACE_ALIGN(64)[1];
        double *__tmp15 = new double DACE_ALIGN(64)[1];
        dace::complex128 *__tmp16 = new dace::complex128 DACE_ALIGN(64)[1];
        double *__tmp18 = new double DACE_ALIGN(64)[1];
        dace::complex128 *__tmp19 = new dace::complex128 DACE_ALIGN(64)[1];
        
        
        {
            dace::complex128 out;

            ///////////////////
            // Tasklet code (init___tmp9)
            out = dace::complex128(0, 1);
            ///////////////////

            __tmp9[0] = out;
        }
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp14)
            out = 1;
            ///////////////////

            __tmp14[0] = out;
        }
        {
            double s1 = fl[0];
            dace::complex128 s2 = __tmp9[0];
            dace::complex128 s3;

            ///////////////////
            // Tasklet code (_SSMult_)
            s3 = (s1 * s2);
            ///////////////////

            __tmp10[0] = s3;
        }
        {
            double s1 = fl[0];
            long long s2 = __tmp14[0];
            double s3;

            ///////////////////
            // Tasklet code (_SSSub_)
            s3 = (s1 - s2);
            ///////////////////

            __tmp18[0] = s3;
        }
        {
            dace::complex128 s1 = __tmp9[0];
            double s2 = __tmp18[0];
            dace::complex128 s3;

            ///////////////////
            // Tasklet code (_SSMult_)
            s3 = (s1 * s2);
            ///////////////////

            __tmp19[0] = s3;
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp10[0];
                        dace::complex128 __in2 = gammaleft[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        sigLl[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp19[0];
                        dace::complex128 __in2 = gammaleft[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        sigGl[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            double s1 = fr[0];
            dace::complex128 s2 = __tmp9[0];
            dace::complex128 s3;

            ///////////////////
            // Tasklet code (_SSMult_)
            s3 = (s1 * s2);
            ///////////////////

            __tmp12[0] = s3;
        }
        {
            double s1 = fr[0];
            long long s2 = __tmp14[0];
            double s3;

            ///////////////////
            // Tasklet code (_SSSub_)
            s3 = (s1 - s2);
            ///////////////////

            __tmp15[0] = s3;
        }
        {
            dace::complex128 s1 = __tmp9[0];
            double s2 = __tmp15[0];
            dace::complex128 s3;

            ///////////////////
            // Tasklet code (_SSMult_)
            s3 = (s1 * s2);
            ///////////////////

            __tmp16[0] = s3;
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp12[0];
                        dace::complex128 __in2 = gammaright[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        sigLr[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp16[0];
                        dace::complex128 __in2 = gammaright[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        sigGr[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        delete[] __tmp10;
        delete[] __tmp12;
        delete[] __tmp15;
        delete[] __tmp16;
        delete[] __tmp18;
        delete[] __tmp19;
    }
    for (n = 0; (n < N); n = (n + 1)) {
        if ((n < (N - 1))) {
            {
                dace::complex128 *__tmp23 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = HE[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __in2 = sigmaRSE[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp23[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp23, HE + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp23;
            }
        } else {
            {
                dace::complex128 *__tmp25 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
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

                                __tmp25[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp25, HE + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp25;
            }
        }
        if ((n > 0)) {
            {
                dace::complex128 *__tmp28 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = HF[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __in2 = sigmaRSF[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp28[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp28, HF + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp28;
            }
        } else {
            {
                dace::complex128 *__tmp30 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
                
                
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

                                __tmp30[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp30, HF + ((BS * BS) * n), (BS * BS), 1);
                delete[] __tmp30;
            }
        }
        {
            dace::complex128 *__tmp33 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            
            
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

                            __tmp33[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp33, HD + ((BS * BS) * n), (BS * BS), 1);
            delete[] __tmp33;
        }
    }
    {
        dace::complex128 *__tmp35 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp39 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp40 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp41 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp44 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp45 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp46 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = HD[((((BS * BS) * (N - 1)) + (BS * __i0)) + __i1)];
                        dace::complex128 __in2 = sigRr[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp35[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp35, gR + ((BS * BS) * (N - 1)), (BS * BS), 1);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = gR[((((BS * BS) * (N - 1)) + (BS * i)) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_gR[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in2 = sigLr[((BS * __i0) + __i1)];
                        dace::complex128 __in1 = sigmaLSD[((((BS * BS) * (N - 1)) + (BS * __i0)) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp39[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * (N - 1))], &__tmp39[0], &__tmp40[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp40[0], &her_gR[0], &__tmp41[0], BS);

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp41, gL + ((BS * BS) * (N - 1)), (BS * BS), 1);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in2 = sigGr[((BS * __i0) + __i1)];
                        dace::complex128 __in1 = sigmaGSD[((((BS * BS) * (N - 1)) + (BS * __i0)) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp44[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * (N - 1))], &__tmp44[0], &__tmp45[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp45[0], &her_gR[0], &__tmp46[0], BS);

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp46, gG + ((BS * BS) * (N - 1)), (BS * BS), 1);
        delete[] __tmp35;
        delete[] __tmp39;
        delete[] __tmp40;
        delete[] __tmp41;
        delete[] __tmp44;
        delete[] __tmp45;
        delete[] __tmp46;
    }
    for (n = (N - 2); (n > (- 1)); n = (n + (- 1))) {
        {
            dace::complex128 *__tmp49 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *sig = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp54 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp58 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp63 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp65 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp67 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp68 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp69 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp70 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp71 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp74 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            
            
            _MatMult__sdfg_1_0_9_29(&HF[((BS * BS) * n)], &gR[((BS * BS) * (n + 1))], &__tmp49[0], BS);
            _MatMult__sdfg_1_0_9_29(&HF[((BS * BS) * n)], &gR[((BS * BS) * (n + 1))], &__tmp54[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp49[0], &HE[((BS * BS) * (n + 1))], &sig[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp54[0], &sigmaLSE[((BS * BS) * (n + 1))], &M[0], BS);
            {
                #pragma omp parallel for
                for (auto i = 0; i < BS; i += 1) {
                    for (auto j = 0; j < BS; j += 1) {
                        {
                            dace::complex128 inp = M[((BS * i) + j)];
                            dace::complex128 out;

                            ///////////////////
                            // Tasklet code (her_trans)
                            out = dace_conj(inp);
                            ///////////////////

                            her_M1[((BS * j) + i)] = out;
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = M[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp68[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in2 = sig[((BS * __i0) + __i1)];
                            dace::complex128 __in1 = HD[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp58[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp58, gR + ((BS * BS) * n), (BS * BS), 1);
            {
                #pragma omp parallel for
                for (auto i = 0; i < BS; i += 1) {
                    for (auto j = 0; j < BS; j += 1) {
                        {
                            dace::complex128 inp = gR[((((BS * BS) * n) + (BS * i)) + j)];
                            dace::complex128 out;

                            ///////////////////
                            // Tasklet code (her_trans)
                            out = dace_conj(inp);
                            ///////////////////

                            her_gR[((BS * j) + i)] = out;
                        }
                    }
                }
            }
            _MatMult__sdfg_1_0_9_29(&HF[((BS * BS) * n)], &gR[((BS * BS) * (n + 1))], &__tmp74[0], BS);
            _MatMult__sdfg_1_0_9_29(&HF[((BS * BS) * n)], &gL[((BS * BS) * (n + 1))], &__tmp63[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp63[0], &HE[((BS * BS) * (n + 1))], &__tmp65[0], BS);
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = __tmp65[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = sigmaLSD[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Add_)
                            __out = (__in1 + __in2);
                            ///////////////////

                            __tmp67[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = __tmp67[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = __tmp68[((BS * __i0) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp69[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &__tmp69[0], &__tmp70[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp70[0], &her_gR[0], &__tmp71[0], BS);

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp71, gL + ((BS * BS) * n), (BS * BS), 1);
            _MatMult__sdfg_1_0_9_29(&__tmp74[0], &sigmaGSE[((BS * BS) * (n + 1))], &__tmp76[0], BS);
            delete[] __tmp49;
            delete[] sig;
            delete[] __tmp54;
            delete[] __tmp58;
            delete[] __tmp63;
            delete[] __tmp65;
            delete[] __tmp67;
            delete[] __tmp68;
            delete[] __tmp69;
            delete[] __tmp70;
            delete[] __tmp71;
            delete[] __tmp74;
        }
        {
            dace::complex128 *__tmp80 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp82 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp84 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp85 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp86 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp87 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            dace::complex128 *__tmp88 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            
            

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp76, M, (BS * BS), 1);
            _MatMult__sdfg_1_0_9_29(&HF[((BS * BS) * n)], &gG[((BS * BS) * (n + 1))], &__tmp80[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp80[0], &HE[((BS * BS) * (n + 1))], &__tmp82[0], BS);
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = __tmp82[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = sigmaGSD[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Add_)
                            __out = (__in1 + __in2);
                            ///////////////////

                            __tmp84[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = M[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp85[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            {
                #pragma omp parallel for
                for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                    for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                        {
                            dace::complex128 __in1 = __tmp84[((BS * __i0) + __i1)];
                            dace::complex128 __in2 = __tmp85[((BS * __i0) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp86[((BS * __i0) + __i1)] = __out;
                        }
                    }
                }
            }
            _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &__tmp86[0], &__tmp87[0], BS);
            _MatMult__sdfg_1_0_9_29(&__tmp87[0], &her_gR[0], &__tmp88[0], BS);

            dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
            __tmp88, gG + ((BS * BS) * n), (BS * BS), 1);
            delete[] __tmp80;
            delete[] __tmp82;
            delete[] __tmp84;
            delete[] __tmp85;
            delete[] __tmp86;
            delete[] __tmp87;
            delete[] __tmp88;
        }
    }
    {
        dace::complex128 *__tmp91 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp97 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp99 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp100 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp101 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp106 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp108 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp109 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp111 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp112 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp113 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp114 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp115 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp118 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                _MatMult__sdfg_1_0_9_29(&HF[0], &gR[(BS * BS)], &__tmp91[0], BS);
                _MatMult__sdfg_1_0_9_29(&HF[0], &gR[(BS * BS)], &__tmp97[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp91[0], &sigmaLSE[(BS * BS)], &M[0], BS);
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < BS; i += 1) {
                        for (auto j = 0; j < BS; j += 1) {
                            {
                                dace::complex128 inp = M[((BS * i) + j)];
                                dace::complex128 out;

                                ///////////////////
                                // Tasklet code (her_trans)
                                out = dace_conj(inp);
                                ///////////////////

                                her_M1[((BS * j) + i)] = out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = M[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp112[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&__tmp97[0], &HE[(BS * BS)], &__tmp99[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = HD[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = __tmp99[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp100[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp100[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = sigRl[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp101[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp101, GR, (BS * BS), 1);
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < BS; i += 1) {
                        for (auto j = 0; j < BS; j += 1) {
                            {
                                dace::complex128 inp = GR[((BS * i) + j)];
                                dace::complex128 out;

                                ///////////////////
                                // Tasklet code (her_trans)
                                out = dace_conj(inp);
                                ///////////////////

                                her_GR[((BS * j) + i)] = out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&HF[0], &gL[(BS * BS)], &__tmp106[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp106[0], &HE[(BS * BS)], &__tmp108[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in2 = __tmp108[((BS * __i0) + __i1)];
                                dace::complex128 __in1 = sigLl[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Add_)
                                __out = (__in1 + __in2);
                                ///////////////////

                                __tmp109[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp109[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = sigmaLSD[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Add_)
                                __out = (__in1 + __in2);
                                ///////////////////

                                __tmp111[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp111[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = __tmp112[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp113[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&GR[0], &__tmp113[0], &__tmp114[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp114[0], &her_GR[0], &__tmp115[0], BS);

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp115, GL, (BS * BS), 1);
            } // End omp section
            #pragma omp section
            {
                _MatMult__sdfg_1_0_9_29(&HF[0], &gR[(BS * BS)], &__tmp118[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp118[0], &sigmaGSE[(BS * BS)], &__tmp120[0], BS);
            } // End omp section
        } // End omp sections
        delete[] __tmp91;
        delete[] __tmp97;
        delete[] __tmp99;
        delete[] __tmp100;
        delete[] __tmp101;
        delete[] __tmp106;
        delete[] __tmp108;
        delete[] __tmp109;
        delete[] __tmp111;
        delete[] __tmp112;
        delete[] __tmp113;
        delete[] __tmp114;
        delete[] __tmp115;
        delete[] __tmp118;
    }
    {
        dace::complex128 *__tmp125 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp127 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp128 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp130 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp131 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp132 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp133 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp134 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp136 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp138 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp139 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp142 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp144 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp145 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp148 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp149 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp150 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp120, M, (BS * BS), 1);
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < BS; i += 1) {
                        for (auto j = 0; j < BS; j += 1) {
                            {
                                dace::complex128 inp = M[((BS * i) + j)];
                                dace::complex128 out;

                                ///////////////////
                                // Tasklet code (her_trans)
                                out = dace_conj(inp);
                                ///////////////////

                                her_M1[((BS * j) + i)] = out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = M[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp131[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&HF[0], &gG[(BS * BS)], &__tmp125[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp125[0], &HE[(BS * BS)], &__tmp127[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in2 = __tmp127[((BS * __i0) + __i1)];
                                dace::complex128 __in1 = sigGl[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Add_)
                                __out = (__in1 + __in2);
                                ///////////////////

                                __tmp128[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp128[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = sigmaGSD[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Add_)
                                __out = (__in1 + __in2);
                                ///////////////////

                                __tmp130[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp130[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = __tmp131[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp132[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&GR[0], &__tmp132[0], &__tmp133[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp133[0], &her_GR[0], &__tmp134[0], BS);

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp134, GG, (BS * BS), 1);
            } // End omp section
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < BS; i += 1) {
                        for (auto j = 0; j < BS; j += 1) {
                            {
                                dace::complex128 inp = gR[(((BS * BS) + (BS * i)) + j)];
                                dace::complex128 out;

                                ///////////////////
                                // Tasklet code (her_trans)
                                out = dace_conj(inp);
                                ///////////////////

                                her_gR[((BS * j) + i)] = out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&GR[0], &HF[0], &__tmp142[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = GL[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_USub_)
                                __out = (- __in1);
                                ///////////////////

                                __tmp136[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&__tmp136[0], &HF[0], &__tmp138[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp138[0], &her_gR[0], &__tmp139[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp142[0], &gL[(BS * BS)], &__tmp144[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp139[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = __tmp144[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Sub_)
                                __out = (__in1 - __in2);
                                ///////////////////

                                __tmp145[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }
                _MatMult__sdfg_1_0_9_29(&GR[0], &sigmaLSF[0], &__tmp148[0], BS);
                _MatMult__sdfg_1_0_9_29(&__tmp148[0], &her_gR[0], &__tmp149[0], BS);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                        for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                            {
                                dace::complex128 __in1 = __tmp145[((BS * __i0) + __i1)];
                                dace::complex128 __in2 = __tmp149[((BS * __i0) + __i1)];
                                dace::complex128 __out;

                                ///////////////////
                                // Tasklet code (_Add_)
                                __out = (__in1 + __in2);
                                ///////////////////

                                __tmp150[((BS * __i0) + __i1)] = __out;
                            }
                        }
                    }
                }

                dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
                __tmp150, GLnd, (BS * BS), 1);
            } // End omp section
        } // End omp sections
        delete[] __tmp125;
        delete[] __tmp127;
        delete[] __tmp128;
        delete[] __tmp130;
        delete[] __tmp131;
        delete[] __tmp132;
        delete[] __tmp133;
        delete[] __tmp134;
        delete[] __tmp136;
        delete[] __tmp138;
        delete[] __tmp139;
        delete[] __tmp142;
        delete[] __tmp144;
        delete[] __tmp145;
        delete[] __tmp148;
        delete[] __tmp149;
        delete[] __tmp150;
    }
    n = 1;
    __state_0_guard_297:;
    if ((n < N)) {
        goto __state_0_slice___tmp0_125;
    }
    if ((! (n < N))) {
        n = 1;
        goto __state_0_guard_304;
    }
    __state_0_slice___tmp0_125:;
    {
        dace::complex128 *__tmp154 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp156 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp158 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp160 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp161 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp165 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp167 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp169 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp174 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp176 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp178 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp183 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp185 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp187 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp188 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp189 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp190 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp191 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp192 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp193 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp196 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp198 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp200 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = gR[((((BS * BS) * n) + (BS * i)) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_gR[((BS * j) + i)] = out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp154[0], BS);
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp165[0], BS);
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp174[0], BS);
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp183[0], BS);
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp196[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp154[0], &GR[((BS * BS) * (n - 1))], &__tmp156[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp156[0], &HF[((BS * BS) * (n - 1))], &__tmp158[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp158[0], &gR[((BS * BS) * n)], &__tmp160[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = gR[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                        dace::complex128 __in2 = __tmp160[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp161[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp161, GR + ((BS * BS) * n), (BS * BS), 1);
        _MatMult__sdfg_1_0_9_29(&__tmp165[0], &GR[((BS * BS) * (n - 1))], &__tmp167[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp167[0], &HF[((BS * BS) * (n - 1))], &__tmp169[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp174[0], &GR[((BS * BS) * (n - 1))], &__tmp176[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp196[0], &GR[((BS * BS) * (n - 1))], &__tmp198[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp198[0], &HF[((BS * BS) * (n - 1))], &__tmp200[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp169[0], &gL[((BS * BS) * n)], &M1[0], BS);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = M1[((BS * i) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_M1[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = M1[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp190[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&__tmp176[0], &sigmaLSF[((BS * BS) * (n - 1))], &__tmp178[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp178[0], &her_gR[0], &M2[0], BS);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = M2[((BS * i) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_M2[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = M2[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = her_M2[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp192[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&__tmp183[0], &GL[((BS * BS) * (n - 1))], &__tmp185[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp185[0], &HF[((BS * BS) * (n - 1))], &__tmp187[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp187[0], &her_gR[0], &__tmp188[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = gL[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                        dace::complex128 __in2 = __tmp188[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp189[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp189[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp190[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp191[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp191[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp192[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp193[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp193, GL + ((BS * BS) * n), (BS * BS), 1);
        _MatMult__sdfg_1_0_9_29(&__tmp200[0], &gG[((BS * BS) * n)], &__tmp202[0], BS);
        delete[] __tmp154;
        delete[] __tmp156;
        delete[] __tmp158;
        delete[] __tmp160;
        delete[] __tmp161;
        delete[] __tmp165;
        delete[] __tmp167;
        delete[] __tmp169;
        delete[] __tmp174;
        delete[] __tmp176;
        delete[] __tmp178;
        delete[] __tmp183;
        delete[] __tmp185;
        delete[] __tmp187;
        delete[] __tmp188;
        delete[] __tmp189;
        delete[] __tmp190;
        delete[] __tmp191;
        delete[] __tmp192;
        delete[] __tmp193;
        delete[] __tmp196;
        delete[] __tmp198;
        delete[] __tmp200;
    }
    goto __state_0_assign_142_8;
    __state_0_guard_304:;
    if ((n < (N - 1))) {
        goto __state_0_slice___tmp4_157;
    }
    if ((! (n < (N - 1)))) {
        goto __state_0_UnaryOp_163;
    }
    __state_0_assign_142_8:;
    {
        dace::complex128 *__tmp205 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp207 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp209 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp214 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp216 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp218 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp219 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp220 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp221 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp222 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp223 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp224 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp202, M1, (BS * BS), 1);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = M1[((BS * i) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_M1[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = M1[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = her_M1[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp221[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp205[0], BS);
        _MatMult__sdfg_1_0_9_29(&gR[((BS * BS) * n)], &HE[((BS * BS) * n)], &__tmp214[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp205[0], &GR[((BS * BS) * (n - 1))], &__tmp207[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp207[0], &sigmaGSF[((BS * BS) * (n - 1))], &__tmp209[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp209[0], &her_gR[0], &M2[0], BS);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = M2[((BS * i) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_M2[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = M2[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = her_M2[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp223[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&__tmp214[0], &GG[((BS * BS) * (n - 1))], &__tmp216[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp216[0], &HF[((BS * BS) * (n - 1))], &__tmp218[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp218[0], &her_gR[0], &__tmp219[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = gG[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                        dace::complex128 __in2 = __tmp219[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp220[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp220[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp221[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp222[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp222[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp223[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp224[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp224, GG + ((BS * BS) * n), (BS * BS), 1);
        delete[] __tmp205;
        delete[] __tmp207;
        delete[] __tmp209;
        delete[] __tmp214;
        delete[] __tmp216;
        delete[] __tmp218;
        delete[] __tmp219;
        delete[] __tmp220;
        delete[] __tmp221;
        delete[] __tmp222;
        delete[] __tmp223;
        delete[] __tmp224;
    }
    if ((n != (N - 1))) {
        goto __state_0_slice___tmp0_151;
    }
    if ((! (n != (N - 1)))) {
        n = (n + 1);
        goto __state_0_guard_297;
    }
    __state_0_slice___tmp4_157:;
    {
        dace::complex128 *trace_tmp = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        _MatMult__sdfg_1_0_9_29(&GLnd[((BS * BS) * (n - 1))], &HE[((BS * BS) * n)], &trace_tmp[0], BS);
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                {
                    dace::complex128 __in2 = trace_tmp[((BS * i) + i)];
                    dace::complex128 __in1 = dTGL[n];
                    dace::complex128 __out;

                    ///////////////////
                    // Tasklet code (augassign_159_12)
                    __out = (__in1 + __in2);
                    ///////////////////

                    dTGL[n] = __out;
                }
            }
        }
        delete[] trace_tmp;
    }
    n = (n + 1);
    goto __state_0_guard_304;
    __state_0_UnaryOp_163:;
    {
        dace::complex128 *__tmp245 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp247 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp249 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *trace_tmp0 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp252 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp254 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *trace_tmp1 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = sigGl[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_USub_)
                        __out = (- __in1);
                        ///////////////////

                        __tmp245[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&__tmp245[0], &GL[0], &__tmp247[0], BS);
        _MatMult__sdfg_1_0_9_29(&GG[0], &sigLl[0], &__tmp249[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp247[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp249[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        trace_tmp0[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&sigGr[0], &GL[((BS * BS) * (N - 1))], &__tmp252[0], BS);
        _MatMult__sdfg_1_0_9_29(&GG[((BS * BS) * (N - 1))], &sigLr[0], &__tmp254[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp252[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp254[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        trace_tmp1[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                {
                    dace::complex128 __in2 = trace_tmp0[((BS * i) + i)];
                    dace::complex128 __in1 = dTGL[0];
                    dace::complex128 __out;

                    ///////////////////
                    // Tasklet code (augassign_166_8)
                    __out = (__in1 + __in2);
                    ///////////////////

                    dTGL[0] = __out;
                }
                {
                    dace::complex128 __in1 = dTGL[(N - 1)];
                    dace::complex128 __in2 = trace_tmp1[((BS * i) + i)];
                    dace::complex128 __out;

                    ///////////////////
                    // Tasklet code (augassign_167_8)
                    __out = (__in1 + __in2);
                    ///////////////////

                    dTGL[(N - 1)] = __out;
                }
            }
        }
        delete[] __tmp245;
        delete[] __tmp247;
        delete[] __tmp249;
        delete[] trace_tmp0;
        delete[] __tmp252;
        delete[] __tmp254;
        delete[] trace_tmp1;
    }
    goto __state_exit_0_sdfg;
    __state_0_slice___tmp0_151:;
    {
        dace::complex128 *__tmp227 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp229 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp230 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp233 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp235 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp236 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp239 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp240 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        dace::complex128 *__tmp241 = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < BS; i += 1) {
                for (auto j = 0; j < BS; j += 1) {
                    {
                        dace::complex128 inp = gR[((((BS * BS) * (n + 1)) + (BS * i)) + j)];
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (her_trans)
                        out = dace_conj(inp);
                        ///////////////////

                        her_gR[((BS * j) + i)] = out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = GL[((((BS * BS) * n) + (BS * __i0)) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_USub_)
                        __out = (- __in1);
                        ///////////////////

                        __tmp227[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&__tmp227[0], &HF[((BS * BS) * n)], &__tmp229[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp229[0], &her_gR[0], &__tmp230[0], BS);
        _MatMult__sdfg_1_0_9_29(&GR[((BS * BS) * n)], &HF[((BS * BS) * n)], &__tmp233[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp233[0], &gL[((BS * BS) * (n + 1))], &__tmp235[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp230[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp235[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Sub_)
                        __out = (__in1 - __in2);
                        ///////////////////

                        __tmp236[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        _MatMult__sdfg_1_0_9_29(&GR[((BS * BS) * n)], &sigmaLSF[((BS * BS) * n)], &__tmp239[0], BS);
        _MatMult__sdfg_1_0_9_29(&__tmp239[0], &her_gR[0], &__tmp240[0], BS);
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    {
                        dace::complex128 __in1 = __tmp236[((BS * __i0) + __i1)];
                        dace::complex128 __in2 = __tmp240[((BS * __i0) + __i1)];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __tmp241[((BS * __i0) + __i1)] = __out;
                    }
                }
            }
        }

        dace::CopyNDDynamic<dace::complex128, 1, false, 1>::template ConstDst<1>::Copy(
        __tmp241, GLnd + ((BS * BS) * n), (BS * BS), 1);
        delete[] __tmp227;
        delete[] __tmp229;
        delete[] __tmp230;
        delete[] __tmp233;
        delete[] __tmp235;
        delete[] __tmp236;
        delete[] __tmp239;
        delete[] __tmp240;
        delete[] __tmp241;
    }
    n = (n + 1);
    goto __state_0_guard_297;
    __state_exit_0_sdfg:;
    delete[] __tmp9;
    delete[] __tmp14;
    delete[] sigLl;
    delete[] sigLr;
    delete[] sigGr;
    delete[] sigGl;
    delete[] gR;
    delete[] her_gR;
    delete[] gL;
    delete[] gG;
    delete[] M;
    delete[] her_M1;
    delete[] __tmp76;
    delete[] GR;
    delete[] her_GR;
    delete[] __tmp120;
    delete[] GLnd;
    delete[] M1;
    delete[] M2;
    delete[] her_M2;
    delete[] __tmp202;
}

DACE_EXPORTED void __program_rgf_dense(dace::complex128 * __restrict__ GG, dace::complex128 * __restrict__ GL, dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ dTGL, double * __restrict__ fl, double * __restrict__ fr, dace::complex128 * __restrict__ gammaleft, dace::complex128 * __restrict__ gammaright, dace::complex128 * __restrict__ sigRl, dace::complex128 * __restrict__ sigRr, dace::complex128 * __restrict__ sigmaGSD, dace::complex128 * __restrict__ sigmaGSE, dace::complex128 * __restrict__ sigmaGSF, dace::complex128 * __restrict__ sigmaLSD, dace::complex128 * __restrict__ sigmaLSE, dace::complex128 * __restrict__ sigmaLSF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    __program_rgf_dense_internal(GG, GL, HD, HE, HF, dTGL, fl, fr, gammaleft, gammaright, sigRl, sigRr, sigmaGSD, sigmaGSE, sigmaGSF, sigmaLSD, sigmaLSE, sigmaLSF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
}

DACE_EXPORTED int __dace_init_rgf_dense(dace::complex128 * __restrict__ GG, dace::complex128 * __restrict__ GL, dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ dTGL, double * __restrict__ fl, double * __restrict__ fr, dace::complex128 * __restrict__ gammaleft, dace::complex128 * __restrict__ gammaright, dace::complex128 * __restrict__ sigRl, dace::complex128 * __restrict__ sigRr, dace::complex128 * __restrict__ sigmaGSD, dace::complex128 * __restrict__ sigmaGSE, dace::complex128 * __restrict__ sigmaGSF, dace::complex128 * __restrict__ sigmaLSD, dace::complex128 * __restrict__ sigmaLSE, dace::complex128 * __restrict__ sigmaLSF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_rgf_dense(dace::complex128 * __restrict__ GG, dace::complex128 * __restrict__ GL, dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ HF, dace::complex128 * __restrict__ dTGL, double * __restrict__ fl, double * __restrict__ fr, dace::complex128 * __restrict__ gammaleft, dace::complex128 * __restrict__ gammaright, dace::complex128 * __restrict__ sigRl, dace::complex128 * __restrict__ sigRr, dace::complex128 * __restrict__ sigmaGSD, dace::complex128 * __restrict__ sigmaGSE, dace::complex128 * __restrict__ sigmaGSF, dace::complex128 * __restrict__ sigmaLSD, dace::complex128 * __restrict__ sigmaLSE, dace::complex128 * __restrict__ sigmaLSF, dace::complex128 * __restrict__ sigmaRSD, dace::complex128 * __restrict__ sigmaRSE, dace::complex128 * __restrict__ sigmaRSF, int BS, int N)
{
}

