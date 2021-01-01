/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _Transpose__sdfg_1_0_0_5(float* _inp, float* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 48; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    {
                        float __inp = _inp[((24 * __i0) + __i1)];
                        float __out;

                        ///////////////////
                        // Tasklet code (transpose)
                        __out = __inp;
                        ///////////////////

                        _out[(__i0 + (48 * __i1))] = __out;
                    }
                }
            }
        }
    }
    
}

inline void _Transpose__sdfg_0_0_6(float* _inp, float* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 12; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 48; __i1 += 1) {
                    {
                        float __inp = _inp[((48 * __i0) + __i1)];
                        float __out;

                        ///////////////////
                        // Tasklet code (transpose)
                        __out = __inp;
                        ///////////////////

                        _out[(__i0 + (12 * __i1))] = __out;
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_0_0_7(float* _a, float* _b, float* _c) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 24; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 12; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((12 * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 12; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < 48; __i2 += 1) {
                        {
                            float __a = _a[((48 * __i0) + __i2)];
                            float __b = _b[(__i1 + (12 * __i2))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_c + ((12 * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_matrix_product_transpose_test_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{

    {
        float *__tmp0 = new float DACE_ALIGN(64)[1152];
        float *__tmp1 = new float DACE_ALIGN(64)[576];
        
        
        _Transpose__sdfg_1_0_0_5(&A[0], &__tmp0[0]);
        _Transpose__sdfg_0_0_6(&B[0], &__tmp1[0]);
        _MatMult__sdfg_0_0_7(&__tmp0[0], &__tmp1[0], &C[0]);
        delete[] __tmp0;
        delete[] __tmp1;
    }
}

DACE_EXPORTED void __program_matrix_product_transpose_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
    __program_matrix_product_transpose_test_internal(A, B, C);
}

DACE_EXPORTED int __dace_init_matrix_product_transpose_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_matrix_product_transpose_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
}

