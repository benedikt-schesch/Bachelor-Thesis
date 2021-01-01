/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_1_0_0_9(float* _a, float* _b, float* _c) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 24; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 48; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((48 * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 48; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < 12; __i2 += 1) {
                        {
                            float __a = _a[((12 * __i0) + __i2)];
                            float __b = _b[(__i1 + (48 * __i2))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_c + ((48 * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_2_0_0_10(float* _a, float* _x, float* _y) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 24; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (gemv_init)
                    out = 0;
                    ///////////////////

                    _y[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 48; __i1 += 1) {
                    {
                        float __a = _a[((48 * __i0) + __i1)];
                        float __x = _x[__i1];
                        float __out;

                        ///////////////////
                        // Tasklet code (_GEMV_)
                        __out = (__a * __x);
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_y + __i0, __out);
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_0_0_11(float* _x, float* _y, float* _result) {

    {
        
        
        {
            float _out;

            ///////////////////
            // Tasklet code (dot_init)
            _out = 0;
            ///////////////////

            _result[0] = _out;
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i = 0; __i < 24; __i += 1) {
                {
                    float __x = _x[__i];
                    float __y = _y[__i];
                    float __out;

                    ///////////////////
                    // Tasklet code (_DOT_)
                    __out = (__x * __y);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_result, __out);
                }
            }
        }
    }
    
}

void __program_matmul_delegation_test_internal(float * __restrict__ matrix0, float * __restrict__ matrix1, float * __restrict__ result, float * __restrict__ vector0, float * __restrict__ vector1)
{

    {
        float *__tmp0 = new float DACE_ALIGN(64)[1152];
        float *__tmp1 = new float DACE_ALIGN(64)[24];
        float *__tmp2 = new float DACE_ALIGN(64)[1];
        
        
        _MatMult__sdfg_1_0_0_9(&matrix0[0], &matrix1[0], &__tmp0[0]);
        _MatMult__sdfg_2_0_0_10(&__tmp0[0], &vector0[0], &__tmp1[0]);
        _MatMult__sdfg_0_0_11(&__tmp1[0], &vector1[0], &__tmp2[0]);
        {
            float __inp = __tmp2[0];
            float __out;

            ///////////////////
            // Tasklet code (assign_14_4)
            __out = __inp;
            ///////////////////

            result[0] = __out;
        }
        delete[] __tmp0;
        delete[] __tmp1;
        delete[] __tmp2;
    }
}

DACE_EXPORTED void __program_matmul_delegation_test(float * __restrict__ matrix0, float * __restrict__ matrix1, float * __restrict__ result, float * __restrict__ vector0, float * __restrict__ vector1)
{
    __program_matmul_delegation_test_internal(matrix0, matrix1, result, vector0, vector1);
}

DACE_EXPORTED int __dace_init_matmul_delegation_test(float * __restrict__ matrix0, float * __restrict__ matrix1, float * __restrict__ result, float * __restrict__ vector0, float * __restrict__ vector1)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_matmul_delegation_test(float * __restrict__ matrix0, float * __restrict__ matrix1, float * __restrict__ result, float * __restrict__ vector0, float * __restrict__ vector1)
{
}

