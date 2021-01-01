#include <chrono>

{
    
    
    {
        auto __dace_tbegin_3_0_0 = std::chrono::high_resolution_clock::now();
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
        auto __dace_tend_3_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_3_0_0 = __dace_tend_3_0_0 - __dace_tbegin_3_0_0;
        dace::perf::report.add("timer_Map reduce_values", __dace_tdiff_3_0_0.count());
    }
}

