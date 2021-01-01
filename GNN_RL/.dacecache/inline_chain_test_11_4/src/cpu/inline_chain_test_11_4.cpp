#include <chrono>

{
    
    
    {
        auto __dace_tbegin_1_0_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto j = 0; j < 20; j += 1) {
            {
                double inA = __tmp_14_23_in_from_1_0[j];
                double out;

                ///////////////////
                // Tasklet code (inline_chain_test_11_4_13)
                out = (inA + 1);
                ///////////////////

                __tmp_15_23_out_of_1_1[j] = out;
            }
        }
        auto __dace_tend_1_0_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_0_0 = __dace_tend_1_0_0 - __dace_tbegin_1_0_0;
        dace::perf::report.add("timer_Map inline_chain_test_11_4_12", __dace_tdiff_1_0_0.count());
    }
    {
        #pragma omp parallel for
        for (auto j = 0; j < 20; j += 1) {
            {
                double intmp = __tmp_15_23_out_of_1_1[j];
                double out;

                ///////////////////
                // Tasklet code (inline_chain_test_11_4_19)
                out = (intmp + 1);
                ///////////////////

                __tmp_21_23_out_of_2_1[j] = out;
            }
        }
    }
}

