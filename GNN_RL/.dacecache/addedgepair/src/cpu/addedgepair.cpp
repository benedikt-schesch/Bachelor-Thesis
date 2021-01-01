/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_addedgepair_internal(double * __restrict__ A, double * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_3 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 31; i += 1) {
                {
                    double a = A[i];
                    double b;

                    ///////////////////
                    // Tasklet code (do)
                    b = (2 * a);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(B, b);
                }
            }
            auto __dace_tend_0_0_3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_3 = __dace_tend_0_0_3 - __dace_tbegin_0_0_3;
            dace::perf::report.add("timer_Map m", __dace_tdiff_0_0_3.count());
        }
    }
    dace::perf::report.save(".dacecache/addedgepair/perf");
}

DACE_EXPORTED void __program_addedgepair(double * __restrict__ A, double * __restrict__ B)
{
    __program_addedgepair_internal(A, B);
}

DACE_EXPORTED int __dace_init_addedgepair(double * __restrict__ A, double * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_addedgepair(double * __restrict__ A, double * __restrict__ B)
{
}

