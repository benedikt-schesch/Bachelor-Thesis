#include <chrono>

{
    
    
    {
        auto __dace_tbegin_2_0_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_2_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_2_0_0 = __dace_tend_2_0_0 - __dace_tbegin_2_0_0;
        dace::perf::report.add("timer_Map gemv_init_map", __dace_tdiff_2_0_0.count());
    }
}
{
    
    
    {
        auto __dace_tbegin_2_1_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_2_1_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_2_1_0 = __dace_tend_2_1_0 - __dace_tbegin_2_1_0;
        dace::perf::report.add("timer_Map _GEMV__map", __dace_tdiff_2_1_0.count());
    }
}

