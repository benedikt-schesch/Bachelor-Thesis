#include <chrono>

{
    
    
    {
        auto __dace_tbegin_2_0_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
            {
                double out;

                ///////////////////
                // Tasklet code (reduce_init)
                out = 0;
                ///////////////////

                _out[_o0] = out;
            }
        }
        auto __dace_tend_2_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_2_0_0 = __dace_tend_2_0_0 - __dace_tbegin_2_0_0;
        dace::perf::report.add("timer_Map reduce_init_map", __dace_tdiff_2_0_0.count());
    }
}
{
    
    
    {
        auto __dace_tbegin_2_1_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
            {
                for (auto _i0 = 0; _i0 < M; _i0 += 1) {
                    {
                        double inp = _in[((N * _i0) + _o0)];
                        double out;

                        ///////////////////
                        // Tasklet code (identity)
                        out = inp;
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce(_out + _o0, out);
                    }
                }
            }
        }
        auto __dace_tend_2_1_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_2_1_0 = __dace_tend_2_1_0 - __dace_tbegin_2_1_0;
        dace::perf::report.add("timer_Map reduce_output", __dace_tdiff_2_1_0.count());
    }
}

