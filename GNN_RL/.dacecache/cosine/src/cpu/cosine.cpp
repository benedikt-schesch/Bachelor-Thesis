/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_cosine_internal(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    {
                        dace::complex64 __inp = A[((24 * __i0) + __i1)];
                        dace::complex64 __out;

                        ///////////////////
                        // Tasklet code (cos)
                        __out = cos(__inp);
                        ///////////////////

                        B[((24 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map cos_map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/cosine/perf");
}

DACE_EXPORTED void __program_cosine(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    __program_cosine_internal(A, B);
}

DACE_EXPORTED int __dace_init_cosine(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_cosine(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
}

