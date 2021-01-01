/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_dot_internal(float * __restrict__ A, float * __restrict__ B, double * __restrict__ out, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                {
                    float a = A[i];
                    float b = B[i];
                    double o;

                    ///////////////////
                    // Tasklet code (product)
                    o = (a * b);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(out, o);
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map product", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/dot/perf");
}

DACE_EXPORTED void __program_dot(float * __restrict__ A, float * __restrict__ B, double * __restrict__ out, int N)
{
    __program_dot_internal(A, B, out, N);
}

DACE_EXPORTED int __dace_init_dot(float * __restrict__ A, float * __restrict__ B, double * __restrict__ out, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dot(float * __restrict__ A, float * __restrict__ B, double * __restrict__ out, int N)
{
}

