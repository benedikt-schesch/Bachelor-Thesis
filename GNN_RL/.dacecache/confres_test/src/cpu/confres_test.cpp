/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_1_0_1_9(float* _in, float* _out, int H, int W) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < W; _i0 += 1) {
                for (auto _i1 = 0; _i1 < H; _i1 += 1) {
                    {
                        float inp = _in[((H * _i0) + _i1)];
                        float out;

                        ///////////////////
                        // Tasklet code (identity)
                        out = inp;
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_out, out);
                    }
                }
            }
        }
    }
    
}

inline void reduce_2_0_1_10(float* _in, float* _out, int H, int W) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < (H - 4); _i0 += 1) {
                for (auto _i1 = 0; _i1 < 1; _i1 += 1) {
                    for (auto _i2 = 0; _i2 < H; _i2 += 1) {
                        {
                            float inp = _in[((((H * W) * _i0) + (H * _i1)) + _i2)];
                            float out;

                            ///////////////////
                            // Tasklet code (identity)
                            out = inp;
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_out, out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void reduce_3_0_1_11(float* _in, float* _out, int H, int W) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 2; _o0 += 1) {
                {
                    for (auto _i0 = 0; _i0 < (H - 6); _i0 += 1) {
                        for (auto _i1 = 0; _i1 < H; _i1 += 1) {
                            {
                                float inp = _in[((((H * W) * _i0) + (H * _o0)) + _i1)];
                                float out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_out + _o0, out);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

inline void reduce_0_1_12(float* _in, float* _out, int H, int W) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < (H - 4); _i0 += 1) {
                for (auto _i1 = 0; _i1 < 1; _i1 += 1) {
                    for (auto _i2 = 0; _i2 < H; _i2 += 1) {
                        {
                            float inp = _in[((((H * W) * _i0) + (H * _i1)) + _i2)];
                            float out;

                            ///////////////////
                            // Tasklet code (identity)
                            out = inp;
                            ///////////////////

                            dace::wcr_custom<float>:: template reduce_atomic([] (const float& a, const float& b) { return (a - b); }, _out, out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_confres_test_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ red1, float * __restrict__ red2, int H, int W)
{
    float *__tmp5 = new float DACE_ALIGN(64)[1];

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < (H - 1); i += 1) {
                for (auto j = 0; j < (W - 1); j += 1) {
                    {
                        float a = A[((H * j) + i)];
                        float b;
                        float c;
                        float r1;
                        float r2;

                        ///////////////////
                        // Tasklet code (compute)
                        b = a;
                        c = (5 * b);
                        r1 = 1;
                        r2 = 2;
                        ///////////////////

                        B[(((H * W) * i) + (H * j))] = b;
                        A[(((H * (j + 1)) + i) + 1)] = c;
                        dace::wcr_fixed<dace::ReductionType::Product, float>::reduce_atomic(red1 + 1, r1);
                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(red2, r2);
                    }
                }
            }
        }
    }
    {
        float *__tmp1 = new float DACE_ALIGN(64)[1];
        float *__tmp3 = new float DACE_ALIGN(64)[2];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                reduce_1_0_1_9(&A[0], &red2[0], H, W);
            } // End omp section
            #pragma omp section
            {
                reduce_2_0_1_10(&B[(((2 * H) * W) + (5 * H))], &__tmp1[0], H, W);
                {
                    float __inp = __tmp1[0];
                    float __out;

                    ///////////////////
                    // Tasklet code (assign_30_4)
                    __out = __inp;
                    ///////////////////

                    red1[0] = __out;
                }
            } // End omp section
            #pragma omp section
            {
                reduce_3_0_1_11(&B[(((3 * H) * W) + (5 * H))], &__tmp3[0], H, W);

                dace::CopyND<float, 1, false, 2>::template ConstDst<1>::Copy(
                __tmp3, red1 + 1, 1);
            } // End omp section
            #pragma omp section
            {
                reduce_0_1_12(&B[(((2 * H) * W) + (5 * H))], &__tmp5[0], H, W);
            } // End omp section
        } // End omp sections
        delete[] __tmp1;
        delete[] __tmp3;
    }
    {
        
        
        {
            float __inp = __tmp5[0];
            float __out;

            ///////////////////
            // Tasklet code (assign_32_4)
            __out = __inp;
            ///////////////////

            red1[0] = __out;
        }
    }
    delete[] __tmp5;
}

DACE_EXPORTED void __program_confres_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ red1, float * __restrict__ red2, int H, int W)
{
    __program_confres_test_internal(A, B, red1, red2, H, W);
}

DACE_EXPORTED int __dace_init_confres_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ red1, float * __restrict__ red2, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_confres_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ red1, float * __restrict__ red2, int H, int W)
{
}

