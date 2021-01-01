#include <chrono>

{
    
    
    {
        double _out;

        ///////////////////
        // Tasklet code (dot_init)
        _out = 0;
        ///////////////////

        _result[0] = _out;
    }
}
{
    
    
    {
        auto __dace_tbegin_1_1_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto __i = 0; __i < n; __i += 1) {
            {
                double __x = _x[__i];
                double __y = _y[__i];
                double __out;

                ///////////////////
                // Tasklet code (_DOT_)
                __out = (__x * __y);
                ///////////////////

                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_result, __out);
            }
        }
        auto __dace_tend_1_1_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_1_0 = __dace_tend_1_1_0 - __dace_tbegin_1_1_0;
        dace::perf::report.add("timer_Map _DOT__map", __dace_tdiff_1_1_0.count());
    }
}

