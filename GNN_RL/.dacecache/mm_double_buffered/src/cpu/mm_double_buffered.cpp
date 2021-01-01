/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void nested_MapState_0_0_5(float* A, float* B, float* C) {
    float trans_A[2048]  DACE_ALIGN(64);
    float trans_B[2048]  DACE_ALIGN(64);
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

                                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(C + ((256 * i) + j), c);
                                    }
                                }
                            }
                        }
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

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(C + ((256 * i) + j), c);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_mm_double_buffered_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < 256; tile_i += 128) {
                for (auto tile_j = 0; tile_j < 256; tile_j += 128) {
                    nested_MapState_0_0_5(&A[(256 * tile_i)], &B[tile_j], &C[((256 * tile_i) + tile_j)]);
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map mm_double_buffered_14", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/mm_double_buffered/perf");
}

DACE_EXPORTED void __program_mm_double_buffered(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
    __program_mm_double_buffered_internal(A, B, C);
}

DACE_EXPORTED int __dace_init_mm_double_buffered(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mm_double_buffered(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C)
{
}

