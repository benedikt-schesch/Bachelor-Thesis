#include <chrono>
float *trans_A = new float DACE_ALIGN(64)[2048];
float *trans_B = new float DACE_ALIGN(64)[2048];
long long tile_k;

{
    
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {

            dace::CopyND<float, 1, false, 128, 8>::template ConstDst<8, 1>::Copy(
            A, trans_A, 256, 1);
        } // End omp section
        #pragma omp section
        {

            dace::CopyND<float, 1, false, 8, 128>::template ConstDst<128, 1>::Copy(
            B, trans_B, 256, 1);
        } // End omp section
    } // End omp sections
}
for (tile_k = 0; (tile_k < 248); tile_k = (tile_k + 8)) {
    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    auto __dace_tbegin_1_0_0 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto k = 0; k < 8; k += 1) {
                        for (auto i = 0; i < 128; i += 1) {
                            for (auto j = 0; j < 128; j += 1) {
                                {
                                    float a = trans_A[(((8 * i) + k) + (1024 * ((tile_k / 8) % 2)))];
                                    float b = trans_B[((j + (128 * k)) + (1024 * ((tile_k / 8) % 2)))];
                                    float c;

                                    ///////////////////
                                    // Tasklet code (mm_double_buffered_14_4_16_8_19)
                                    c = (a * b);
                                    ///////////////////

                                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(C + ((256 * i) + j), c);
                                }
                            }
                        }
                    }
                    auto __dace_tend_1_0_0 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_1_0_0 = __dace_tend_1_0_0 - __dace_tbegin_1_0_0;
                    dace::perf::report.add("timer_Map mm_double_buffered_14_4_16_8_18", __dace_tdiff_1_0_0.count());
                }
            } // End omp section
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 128, 8>::template ConstDst<8, 1>::Copy(
                A + (tile_k + 8), trans_A + (1024 * (((tile_k / 8) + 1) % 2)), 256, 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 8, 128>::template ConstDst<128, 1>::Copy(
                B + ((256 * tile_k) + 2048), trans_B + (1024 * (((tile_k / 8) + 1) % 2)), 256, 1);
            } // End omp section
        } // End omp sections
    }
}
{
    
    
    {
        auto __dace_tbegin_1_2_0 = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for
        for (auto k = 0; k < 8; k += 1) {
            for (auto i = 0; i < 128; i += 1) {
                for (auto j = 0; j < 128; j += 1) {
                    {
                        float a = trans_A[(((8 * i) + k) + (1024 * ((tile_k / 8) % 2)))];
                        float b = trans_B[((j + (128 * k)) + (1024 * ((tile_k / 8) % 2)))];
                        float c;

                        ///////////////////
                        // Tasklet code (mm_double_buffered_14_4_16_8_19)
                        c = (a * b);
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(C + ((256 * i) + j), c);
                    }
                }
            }
        }
        auto __dace_tend_1_2_0 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> __dace_tdiff_1_2_0 = __dace_tend_1_2_0 - __dace_tbegin_1_2_0;
        dace::perf::report.add("timer_Map mm_double_buffered_14_4_16_8_18", __dace_tdiff_1_2_0.count());
    }
}
delete[] trans_A;
delete[] trans_B;

