#include <chrono>
#include <chrono>
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

#include <chrono>
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
                auto __dace_tbegin_1_0_2 = std::chrono::high_resolution_clock::now();
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
                auto __dace_tend_1_0_2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> __dace_tdiff_1_0_2 = __dace_tend_1_0_2 - __dace_tbegin_1_0_2;
                dace::perf::report.add("timer_Map _Sub__map", __dace_tdiff_1_0_2.count());
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
        auto __dace_tbegin_1_1_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_1_1_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_1_0 = __dace_tend_1_1_0 - __dace_tbegin_1_1_0;
        dace::perf::report.add("timer_Map augassign_13_4_map", __dace_tdiff_1_1_0.count());
    }
}
delete[] tmp_sum;

