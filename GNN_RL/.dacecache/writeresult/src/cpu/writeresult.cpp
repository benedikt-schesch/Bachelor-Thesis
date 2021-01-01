/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_writeresult_internal(double * __restrict__ output, double * __restrict__ values, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    double* o = output;
                    double v;

                    ///////////////////
                    // Tasklet code (writeresult_11)
                    v = dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(output + 5, 1);;
                    ///////////////////

                    values[i] = v;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map writeresult_10", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/writeresult/perf");
}

DACE_EXPORTED void __program_writeresult(double * __restrict__ output, double * __restrict__ values, int N)
{
    __program_writeresult_internal(output, values, N);
}

DACE_EXPORTED int __dace_init_writeresult(double * __restrict__ output, double * __restrict__ values, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_writeresult(double * __restrict__ output, double * __restrict__ values, int N)
{
}

