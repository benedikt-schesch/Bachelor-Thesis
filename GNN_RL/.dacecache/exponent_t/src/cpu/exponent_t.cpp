/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_exponent_t_internal(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 24; i += 1) {
                for (auto j = 0; j < 24; j += 1) {
                    dace::complex64 exponent_t_56_4___tmp1[1]  DACE_ALIGN(64);
                    {
                        dace::complex64 __inp = A[((24 * i) + j)];
                        dace::complex64 __out;

                        ///////////////////
                        // Tasklet code (exp)
                        __out = exp(__inp);
                        ///////////////////

                        exponent_t_56_4___tmp1[0] = __out;
                    }
                    {
                        dace::complex64 __inp = exponent_t_56_4___tmp1[0];
                        dace::complex64 __out;

                        ///////////////////
                        // Tasklet code (assign_57_8)
                        __out = __inp;
                        ///////////////////

                        B[((24 * i) + j)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map exponent_t_56", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/exponent_t/perf");
}

DACE_EXPORTED void __program_exponent_t(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    __program_exponent_t_internal(A, B);
}

DACE_EXPORTED int __dace_init_exponent_t(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_exponent_t(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
}

