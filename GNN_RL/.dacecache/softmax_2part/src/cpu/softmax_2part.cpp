/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_1_0_0_15(float* _in, float* _out, int B, int SM, int SN) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 1; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < 1; _o2 += 1) {
                        {
                            float out;

                            ///////////////////
                            // Tasklet code (reduce_init)
                            out = 0;
                            ///////////////////

                            _out[((_o0 + _o1) + _o2)] = out;
                        }
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 1; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < 1; _o2 += 1) {
                        {
                            for (auto _i0 = 0; _i0 < SM; _i0 += 1) {
                                {
                                    float inp = _in[((((((B * SM) * SN) * _o0) + ((SM * SN) * _o1)) + (SM * _o2)) + _i0)];
                                    float out;

                                    ///////////////////
                                    // Tasklet code (identity)
                                    out = inp;
                                    ///////////////////

                                    dace::wcr_fixed<dace::ReductionType::Max, float>::reduce(_out + ((_o0 + _o1) + _o2), out);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
}

inline void reduce_2_0_0_16(float* _in, float* _out, int B, int SM, int SN) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 1; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < 1; _o2 += 1) {
                        {
                            float out;

                            ///////////////////
                            // Tasklet code (reduce_init)
                            out = 0;
                            ///////////////////

                            _out[((_o0 + _o1) + _o2)] = out;
                        }
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 1; _o1 += 1) {
                    for (auto _o2 = 0; _o2 < 1; _o2 += 1) {
                        {
                            for (auto _i0 = 0; _i0 < SM; _i0 += 1) {
                                {
                                    float inp = _in[((((((B * SM) * SN) * _o0) + ((SM * SN) * _o1)) + (SM * _o2)) + _i0)];
                                    float out;

                                    ///////////////////
                                    // Tasklet code (identity)
                                    out = inp;
                                    ///////////////////

                                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_out + ((_o0 + _o1) + _o2), out);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_softmax_2part_internal(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN)
{

    {
        float *tmp_out = new float DACE_ALIGN(64)[(((B * H) * SM) * SN)];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < B; j += 1) {
                    for (auto k = 0; k < SN; k += 1) {
                        float tmp_max[1]  DACE_ALIGN(64);
                        reduce_1_0_0_15(&X_in[(((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k))], &tmp_max[0], B, SM, SN);
                        {
                            for (auto l = 0; l < SM; l += 1) {
                                {
                                    float inp = X_in[((((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k)) + l)];
                                    float mx = tmp_max[0];
                                    float o;

                                    ///////////////////
                                    // Tasklet code (softmax_29)
                                    o = dace::math::exp((inp - mx));
                                    ///////////////////

                                    tmp_out[((((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k)) + l)] = o;
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < B; j += 1) {
                    for (auto k = 0; k < SN; k += 1) {
                        float tmp_sum[1]  DACE_ALIGN(64);
                        reduce_2_0_0_16(&tmp_out[(((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k))], &tmp_sum[0], B, SM, SN);
                        {
                            for (auto l = 0; l < SM; l += 1) {
                                {
                                    float inp = tmp_out[((((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k)) + l)];
                                    float sm = tmp_sum[0];
                                    float o;

                                    ///////////////////
                                    // Tasklet code (softmax_38)
                                    o = (inp / sm);
                                    ///////////////////

                                    __return[((((((B * SM) * SN) * i) + ((SM * SN) * j)) + (SM * k)) + l)] = o;
                                }
                            }
                        }
                    }
                }
            }
        }
        delete[] tmp_out;
    }
}

DACE_EXPORTED void __program_softmax_2part(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN)
{
    __program_softmax_2part_internal(X_in, __return, B, H, SM, SN);
}

DACE_EXPORTED int __dace_init_softmax_2part(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_softmax_2part(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN)
{
}

