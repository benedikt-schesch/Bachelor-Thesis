#include <chrono>

{
    
    
    {
        auto __dace_tbegin_1_0_3 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto i = 0; i < (n / 4); i += 1) {
            {
                dace::vec<float, 4> x_con = _x[i];
                dace::vec<float, 4> y_con = _y[i];
                dace::vec<float, 4> z_con;

                ///////////////////
                // Tasklet code (vecAdd_task)
                z_con = (x_con + y_con);
                ///////////////////

                _res[i] = z_con;
            }
        }
        auto __dace_tend_1_0_3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_0_3 = __dace_tend_1_0_3 - __dace_tbegin_1_0_3;
        dace::perf::report.add("timer_Map vecAdd_map", __dace_tdiff_1_0_3.count());
    }
}

