/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_multiple_fusions_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ out)
{
    dace::perf::report.reset();

    {
        float *A_prime = new float DACE_ALIGN(64)[200];
        float *A_prime_copy = new float DACE_ALIGN(64)[200];
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    {
                        float inp = A[((20 * i) + j)];
                        float out1;
                        float out2;
                        float out3;

                        ///////////////////
                        // Tasklet code (multiple_fusions_42)
                        out1 = inp;
                        out2 = (inp * inp);
                        out3 = (inp * inp);
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(out, out1);
                        A_prime[((20 * i) + j)] = out2;
                        A_prime_copy[((20 * i) + j)] = out3;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map multiple_fusions_41", __dace_tdiff_0_0_0.count());
        }
        {
            auto __dace_tbegin_0_0_6 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    {
                        float inp = A_prime[((20 * i) + j)];
                        float out1;

                        ///////////////////
                        // Tasklet code (multiple_fusions_52)
                        out1 = (inp + 1);
                        ///////////////////

                        B[((20 * i) + j)] = out1;
                    }
                }
            }
            auto __dace_tend_0_0_6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_6 = __dace_tend_0_0_6 - __dace_tbegin_0_0_6;
            dace::perf::report.add("timer_Map multiple_fusions_51", __dace_tdiff_0_0_6.count());
        }
        {
            auto __dace_tbegin_0_0_9 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    {
                        float inp = A_prime_copy[((20 * i) + j)];
                        float out2;

                        ///////////////////
                        // Tasklet code (multiple_fusions_58)
                        out2 = (inp + 2);
                        ///////////////////

                        C[((20 * i) + j)] = out2;
                    }
                }
            }
            auto __dace_tend_0_0_9 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_9 = __dace_tend_0_0_9 - __dace_tbegin_0_0_9;
            dace::perf::report.add("timer_Map multiple_fusions_57", __dace_tdiff_0_0_9.count());
        }
        delete[] A_prime;
        delete[] A_prime_copy;
    }
    dace::perf::report.save(".dacecache/multiple_fusions/perf");
}

DACE_EXPORTED void __program_multiple_fusions(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ out)
{
    __program_multiple_fusions_internal(A, B, C, out);
}

DACE_EXPORTED int __dace_init_multiple_fusions(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ out)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_multiple_fusions(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ out)
{
}

