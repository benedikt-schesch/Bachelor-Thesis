#include <chrono>

{
    
    
    {
        auto __dace_tbegin_1_0_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto i = 0; i < 1; i += 1) {
            {
                double inp = a[i];
                double out;

                ///////////////////
                // Tasklet code (m)
                out = (inp * 5.0);
                ///////////////////

                b[i] = out;
            }
        }
        auto __dace_tend_1_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_0_0 = __dace_tend_1_0_0 - __dace_tbegin_1_0_0;
        dace::perf::report.add("timer_Map m_map", __dace_tdiff_1_0_0.count());
    }
}

