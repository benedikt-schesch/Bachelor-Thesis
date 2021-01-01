#include <chrono>

{
    
    
    {
        auto __dace_tbegin_1_0_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto __i0 = 0; __i0 < 3; __i0 += 1) {
            for (auto __i1 = 0; __i1 < 3; __i1 += 1) {
                {
                    float __inp = _inp[((3 * __i0) + __i1)];
                    float __out;

                    ///////////////////
                    // Tasklet code (transpose)
                    __out = __inp;
                    ///////////////////

                    _out[(__i0 + (3 * __i1))] = __out;
                }
            }
        }
        auto __dace_tend_1_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_0_0 = __dace_tend_1_0_0 - __dace_tbegin_1_0_0;
        dace::perf::report.add("timer_Map transpose_map", __dace_tdiff_1_0_0.count());
    }
}

