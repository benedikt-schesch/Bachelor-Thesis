/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_tounroll_internal(double * __restrict__ A, double * __restrict__ B)
{
    dace::perf::report.reset();
    long long i;

    {
        
        
        {
            auto __dace_tbegin_0_3_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto j = 0; j < 20; j += 1) {
                {
                    double a = A[j];
                    double b_in = B[j];
                    double b_out;

                    ///////////////////
                    // Tasklet code (tounroll_12)
                    b_out = (b_in + (a * 0));
                    ///////////////////

                    B[j] = b_out;
                }
            }
            auto __dace_tend_0_3_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_3_0 = __dace_tend_0_3_0 - __dace_tbegin_0_3_0;
            dace::perf::report.add("timer_Map tounroll_11", __dace_tdiff_0_3_0.count());
        }
        {
            auto __dace_tbegin_0_3_6 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto j = 0; j < 20; j += 1) {
                {
                    double a = A[j];
                    double b_in = B[j];
                    double b_out;

                    ///////////////////
                    // Tasklet code (tounroll_12)
                    b_out = (b_in + (a * 1));
                    ///////////////////

                    B[j] = b_out;
                }
            }
            auto __dace_tend_0_3_6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_3_6 = __dace_tend_0_3_6 - __dace_tbegin_0_3_6;
            dace::perf::report.add("timer_Map tounroll_11", __dace_tdiff_0_3_6.count());
        }
    }
    for (i = 2; (i < 5); i = (i + 1)) {
        {
            
            
            {
                auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
                #pragma omp parallel for
                for (auto j = 0; j < 20; j += 1) {
                    {
                        double a = A[j];
                        double b_in = B[j];
                        double b_out;

                        ///////////////////
                        // Tasklet code (tounroll_12)
                        b_out = (b_in + (a * i));
                        ///////////////////

                        B[j] = b_out;
                    }
                }
                auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
                dace::perf::report.add("timer_Map tounroll_11", __dace_tdiff_0_0_0.count());
            }
        }
    }
    dace::perf::report.save(".dacecache/tounroll/perf");
}

DACE_EXPORTED void __program_tounroll(double * __restrict__ A, double * __restrict__ B)
{
    __program_tounroll_internal(A, B);
}

DACE_EXPORTED int __dace_init_tounroll(double * __restrict__ A, double * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tounroll(double * __restrict__ A, double * __restrict__ B)
{
}

