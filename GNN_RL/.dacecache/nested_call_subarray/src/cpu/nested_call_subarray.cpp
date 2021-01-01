/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_1_1_0_11(float* _in, float* _out, int N) {

    {
        
        
        {
            #pragma omp parallel for
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
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                {
                    float inp = _in[_i0];
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

inline void reduce_1_0_12(float* _in, float* _out, int N) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < N; _i0 += 1) {
                {
                    float inp = _in[_i0];
                    float out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Max, float>::reduce_atomic(_out, out);
                }
            }
        }
    }
    
}

inline void dace_softmax_0_0_1(float* X_in, float* X_out, int N) {
    float *tmp_sum = new float DACE_ALIGN(64)[1];

    {
        float *tmp_max = new float DACE_ALIGN(64)[1];
        float *__tmp4 = new float DACE_ALIGN(64)[N];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                reduce_1_1_0_11(&X_in[0], &tmp_max[0], N);
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < N; __i0 += 1) {
                        {
                            float __in1 = X_in[__i0];
                            float __in2 = tmp_max[0];
                            float __out;

                            ///////////////////
                            // Tasklet code (_Sub_)
                            __out = (__in1 - __in2);
                            ///////////////////

                            __tmp4[__i0] = __out;
                        }
                    }
                }
                {
                    #pragma omp parallel for
                    for (auto __i0 = 0; __i0 < N; __i0 += 1) {
                        {
                            float __inp = __tmp4[__i0];
                            float __out;

                            ///////////////////
                            // Tasklet code (exp)
                            __out = exp(__inp);
                            ///////////////////

                            X_out[__i0] = __out;
                        }
                    }
                }
            } // End omp section
            #pragma omp section
            {
                reduce_1_0_12(&X_in[0], &tmp_sum[0], N);
            } // End omp section
        } // End omp sections
        delete[] tmp_max;
        delete[] __tmp4;
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < N; __i0 += 1) {
                {
                    float __in1 = X_out[__i0];
                    float __in2 = tmp_sum[0];
                    float __out;

                    ///////////////////
                    // Tasklet code (augassign_13_4)
                    __out = (__in1 / __in2);
                    ///////////////////

                    X_out[__i0] = __out;
                }
            }
        }
    }
    delete[] tmp_sum;
    
}

void __program_nested_call_subarray_internal(float * __restrict__ a, float * __restrict__ b)
{

    {
        
        
        dace_softmax_0_0_1(&a[0], &b[0], 2);
    }
}

DACE_EXPORTED void __program_nested_call_subarray(float * __restrict__ a, float * __restrict__ b)
{
    __program_nested_call_subarray_internal(a, b);
}

DACE_EXPORTED int __dace_init_nested_call_subarray(float * __restrict__ a, float * __restrict__ b)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_call_subarray(float * __restrict__ a, float * __restrict__ b)
{
}

