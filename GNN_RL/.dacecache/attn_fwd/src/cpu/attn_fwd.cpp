/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_1_0_0_27(float* _a, float* _b, float* _c, int Qsize, int projQsize, int seqLenQ) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < projQsize; _o0 += 1) {
                for (auto _o1 = 0; _o1 < seqLenQ; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((_o0 * seqLenQ) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < projQsize; __i0 += 1) {
                for (auto __i1 = 0; __i1 < seqLenQ; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < Qsize; __i2 += 1) {
                        {
                            float __a = _a[((Qsize * __i0) + __i2)];
                            float __b = _b[(__i1 + (__i2 * seqLenQ))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_c + ((__i0 * seqLenQ) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_2_0_0_28(float* _a, float* _b, float* _c, int Qsize, int projQsize, int seqLenK) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < projQsize; _o0 += 1) {
                for (auto _o1 = 0; _o1 < seqLenK; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((_o0 * seqLenK) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < projQsize; __i0 += 1) {
                for (auto __i1 = 0; __i1 < seqLenK; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < Qsize; __i2 += 1) {
                        {
                            float __a = _a[((Qsize * __i0) + __i2)];
                            float __b = _b[(__i1 + (__i2 * seqLenK))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_c + ((__i0 * seqLenK) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_4_0_0_30(float* _a, float* _b, float* _c, int projQsize, int seqLenK, int seqLenQ) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < seqLenK; _o0 += 1) {
                for (auto _o1 = 0; _o1 < seqLenQ; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((_o0 * seqLenQ) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < seqLenK; __i0 += 1) {
                for (auto __i1 = 0; __i1 < seqLenQ; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < projQsize; __i2 += 1) {
                        {
                            float __a = _a[((__i0 * projQsize) + __i2)];
                            float __b = _b[(__i1 + (__i2 * seqLenQ))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_c + ((__i0 * seqLenQ) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void reduce_1_1_0_11(float* _in, float* _out, int N) {

    {
        
        
        {
            for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                {
                    float inp = _in[_i0];
                    float out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Max, float>::reduce(_out, out);
                }
            }
        }
    }
    
}

inline void reduce_2_1_0_12(float* _in, float* _out, int N) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                {
                    float inp = _in[_i0];
                    float out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_out, out);
                }
            }
        }
    }
    
}

inline void dace_softmax_0_0_25(float* X_in, float* X_out, int N) {

    {
        float tmp_max[1]  DACE_ALIGN(64);
        float tmp_sum[1]  DACE_ALIGN(64);
        
        
        reduce_1_1_0_11(&X_in[0], &tmp_max[0], N);
        {
            for (auto i = 0; i < N; i += 1) {
                {
                    float x_in = X_in[i];
                    float x_max = tmp_max[0];
                    float x_out;

                    ///////////////////
                    // Tasklet code (softmax_tasklet_sub)
                    x_out = exp((x_in - x_max));
                    ///////////////////

                    X_out[i] = x_out;
                }
            }
        }
        reduce_2_1_0_12(&X_out[0], &tmp_sum[0], N);
        {
            for (auto i = 0; i < N; i += 1) {
                {
                    float x_in = X_out[i];
                    float x_sum = tmp_sum[0];
                    float x_out;

                    ///////////////////
                    // Tasklet code (softmax_tasklet_div)
                    x_out = (x_in / x_sum);
                    ///////////////////

                    X_out[i] = x_out;
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_5_0_0_31(float* _a, float* _b, float* _c, int projQsize, int seqLenK, int seqLenQ) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < projQsize; _o0 += 1) {
                for (auto _o1 = 0; _o1 < seqLenQ; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((_o0 * seqLenQ) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < projQsize; __i0 += 1) {
                for (auto __i1 = 0; __i1 < seqLenQ; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < seqLenK; __i2 += 1) {
                        {
                            float __a = _a[((__i0 * seqLenK) + __i2)];
                            float __b = _b[(__i1 + (__i2 * seqLenQ))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_c + ((__i0 * seqLenQ) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_0_0_32(float* _b, float* _a, float* _c, int Qsize, int projQsize, int seqLenQ) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < Qsize; _o0 += 1) {
                for (auto _o1 = 0; _o1 < seqLenQ; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((_o0 * seqLenQ) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < Qsize; __i0 += 1) {
                for (auto __i1 = 0; __i1 < seqLenQ; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < projQsize; __i2 += 1) {
                        {
                            float __a = _a[((__i0 * projQsize) + __i2)];
                            float __b = _b[(__i1 + (__i2 * seqLenQ))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_c + ((__i0 * seqLenQ) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void reduce_0_0_26(float* _in, float* _out, int Qsize, int numHeads, int seqLenQ) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                for (auto _o1 = 0; _o1 < Qsize; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < seqLenQ; _o2 += 1) {
                        {
                            for (auto _i0 = 0; _i0 < numHeads; _i0 += 1) {
                                {
                                    float inp = _in[((((Qsize * _i0) * seqLenQ) + (_o0 * seqLenQ)) + _o1)];
                                    float out;

                                    ///////////////////
                                    // Tasklet code (identity)
                                    out = inp;
                                    ///////////////////

                                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_out + ((((Qsize * _o0) * seqLenQ) + (_o1 * seqLenQ)) + _o2), out);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_attn_fwd_internal(float * __restrict__ k, float * __restrict__ out, float * __restrict__ q, float * __restrict__ v, float * __restrict__ wk, float * __restrict__ wo, float * __restrict__ wq, float * __restrict__ wv, int Qsize, int batchSize, int numHeads, int projQsize, int seqLenK, int seqLenQ)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto b = 0; b < batchSize; b += 1) {
                float *attn_fwd_73_4_outs = new float DACE_ALIGN(64)[((Qsize * numHeads) * seqLenQ)];
                {
                    for (auto h = 0; h < numHeads; h += 1) {
                        float *attn_fwd_73_4_77_8___tmp12 = new float DACE_ALIGN(64)[(projQsize * seqLenQ)];
                        float *attn_fwd_73_4_77_8_k_bar = new float DACE_ALIGN(64)[(projQsize * seqLenK)];
                        float *attn_fwd_73_4_77_8___tmp14 = new float DACE_ALIGN(64)[(projQsize * seqLenK)];
                        float *attn_fwd_73_4_77_8_beta = new float DACE_ALIGN(64)[(seqLenK * seqLenQ)];
                        float *attn_fwd_73_4_77_8_k_bar_t = new float DACE_ALIGN(64)[(projQsize * seqLenK)];
                        float *attn_fwd_73_4_77_8___tmp17 = new float DACE_ALIGN(64)[(projQsize * seqLenQ)];
                        float *attn_fwd_73_4_77_8___tmp15 = new float DACE_ALIGN(64)[(seqLenK * seqLenQ)];
                        _MatMult__sdfg_1_0_0_27(&wq[((Qsize * h) * projQsize)], &q[((Qsize * b) * seqLenQ)], &attn_fwd_73_4_77_8___tmp12[0], Qsize, projQsize, seqLenQ);
                        _MatMult__sdfg_2_0_0_28(&wk[((Qsize * h) * projQsize)], &k[((Qsize * b) * seqLenK)], &attn_fwd_73_4_77_8_k_bar[0], Qsize, projQsize, seqLenK);
                        {
                            for (auto i = 0; i < projQsize; i += 1) {
                                for (auto j = 0; j < seqLenK; j += 1) {
                                    {
                                        float __inp = attn_fwd_73_4_77_8_k_bar[((i * seqLenK) + j)];
                                        float __out;

                                        ///////////////////
                                        // Tasklet code (assign_50_8)
                                        __out = __inp;
                                        ///////////////////

                                        attn_fwd_73_4_77_8_k_bar_t[(i + (j * projQsize))] = __out;
                                    }
                                }
                            }
                        }
                        _MatMult__sdfg_4_0_0_30(&attn_fwd_73_4_77_8_k_bar_t[0], &attn_fwd_73_4_77_8___tmp12[0], &attn_fwd_73_4_77_8_beta[0], projQsize, seqLenK, seqLenQ);
                        {
                            for (auto j = 0; j < seqLenK; j += 1) {
                                dace_softmax_0_0_25(&attn_fwd_73_4_77_8_beta[(j * seqLenQ)], &attn_fwd_73_4_77_8___tmp15[(j * seqLenQ)], seqLenQ);
                            }
                        }
                        _MatMult__sdfg_2_0_0_28(&wv[((Qsize * h) * projQsize)], &v[((Qsize * b) * seqLenK)], &attn_fwd_73_4_77_8___tmp14[0], Qsize, projQsize, seqLenK);
                        _MatMult__sdfg_5_0_0_31(&attn_fwd_73_4_77_8___tmp14[0], &attn_fwd_73_4_77_8___tmp15[0], &attn_fwd_73_4_77_8___tmp17[0], projQsize, seqLenK, seqLenQ);
                        _MatMult__sdfg_0_0_32(&attn_fwd_73_4_77_8___tmp17[0], &wo[((Qsize * h) * projQsize)], &attn_fwd_73_4_outs[((Qsize * h) * seqLenQ)], Qsize, projQsize, seqLenQ);
                        delete[] attn_fwd_73_4_77_8___tmp12;
                        delete[] attn_fwd_73_4_77_8_k_bar;
                        delete[] attn_fwd_73_4_77_8___tmp14;
                        delete[] attn_fwd_73_4_77_8_beta;
                        delete[] attn_fwd_73_4_77_8_k_bar_t;
                        delete[] attn_fwd_73_4_77_8___tmp17;
                        delete[] attn_fwd_73_4_77_8___tmp15;
                    }
                }
                reduce_0_0_26(&attn_fwd_73_4_outs[0], &out[((Qsize * b) * seqLenQ)], Qsize, numHeads, seqLenQ);
                delete[] attn_fwd_73_4_outs;
            }
        }
    }
}

DACE_EXPORTED void __program_attn_fwd(float * __restrict__ k, float * __restrict__ out, float * __restrict__ q, float * __restrict__ v, float * __restrict__ wk, float * __restrict__ wo, float * __restrict__ wq, float * __restrict__ wv, int Qsize, int batchSize, int numHeads, int projQsize, int seqLenK, int seqLenQ)
{
    __program_attn_fwd_internal(k, out, q, v, wk, wo, wq, wv, Qsize, batchSize, numHeads, projQsize, seqLenK, seqLenQ);
}

DACE_EXPORTED int __dace_init_attn_fwd(float * __restrict__ k, float * __restrict__ out, float * __restrict__ q, float * __restrict__ v, float * __restrict__ wk, float * __restrict__ wo, float * __restrict__ wq, float * __restrict__ wv, int Qsize, int batchSize, int numHeads, int projQsize, int seqLenK, int seqLenQ)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_attn_fwd(float * __restrict__ k, float * __restrict__ out, float * __restrict__ q, float * __restrict__ v, float * __restrict__ wk, float * __restrict__ wo, float * __restrict__ wq, float * __restrict__ wv, int Qsize, int batchSize, int numHeads, int projQsize, int seqLenK, int seqLenQ)
{
}

