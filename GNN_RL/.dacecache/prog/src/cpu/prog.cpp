/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_prog_internal(double * __restrict__ A, double * __restrict__ stats, int W)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    double inp = A[i];
                    double ssq;
                    double sum;

                    ///////////////////
                    // Tasklet code (compute)
                    sum = inp;
                    ssq = (inp * inp);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(stats + 1, ssq);
                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(stats, sum);
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map compute", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/prog/perf");
}

DACE_EXPORTED void __program_prog(double * __restrict__ A, double * __restrict__ stats, int W)
{
    __program_prog_internal(A, stats, W);
}

DACE_EXPORTED int __dace_init_prog(double * __restrict__ A, double * __restrict__ stats, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_prog(double * __restrict__ A, double * __restrict__ stats, int W)
{
}

