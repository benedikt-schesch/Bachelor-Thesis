#include <chrono>

{
    
    
    {
        auto __dace_tbegin_1_0_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_1_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_0_0 = __dace_tend_1_0_0 - __dace_tbegin_1_0_0;
        dace::perf::report.add("timer_Map gemm_init_map", __dace_tdiff_1_0_0.count());
    }
}
{
    
    
    {
        auto __dace_tbegin_1_1_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_1_1_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_1_0 = __dace_tend_1_1_0 - __dace_tbegin_1_1_0;
        dace::perf::report.add("timer_Map _GEMM__map", __dace_tdiff_1_1_0.count());
    }
}

