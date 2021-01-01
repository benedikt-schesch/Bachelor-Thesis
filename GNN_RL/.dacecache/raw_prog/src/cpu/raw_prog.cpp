/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_raw_prog_internal(double * __restrict__ A, double * __restrict__ B, int W)
{
    dace::perf::report.reset();

    {
        double *tmp = new double DACE_ALIGN(64)[W];
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    double a = A[i];
                    double b;

                    ///////////////////
                    // Tasklet code (compute_tmp)
                    b = a;
                    ///////////////////

                    tmp[i] = b;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map compute_tmp", __dace_tdiff_0_0_0.count());
        }
        {
            auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    double a = tmp[i];
                    double b;

                    ///////////////////
                    // Tasklet code (compute_tmp_again)
                    b = (a + a);
                    ///////////////////

                    tmp[i] = b;
                }
            }
            auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
            dace::perf::report.add("timer_Map compute_tmp_again", __dace_tdiff_0_0_4.count());
        }
        {
            auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    double a = tmp[i];
                    double b;

                    ///////////////////
                    // Tasklet code (compute_output)
                    b = (a + a);
                    ///////////////////

                    B[i] = b;
                }
            }
            auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
            dace::perf::report.add("timer_Map compute_output", __dace_tdiff_0_0_7.count());
        }
        delete[] tmp;
    }
    dace::perf::report.save(".dacecache/raw_prog/perf");
}

DACE_EXPORTED void __program_raw_prog(double * __restrict__ A, double * __restrict__ B, int W)
{
    __program_raw_prog_internal(A, B, W);
}

DACE_EXPORTED int __dace_init_raw_prog(double * __restrict__ A, double * __restrict__ B, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_raw_prog(double * __restrict__ A, double * __restrict__ B, int W)
{
}

