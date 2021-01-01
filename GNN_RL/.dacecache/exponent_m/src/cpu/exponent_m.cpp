/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_exponent_m_internal(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 24; i += 1) {
                {
                    auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
                    for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                        {
                            dace::complex64 __inp = A[(__i0 + (24 * i))];
                            dace::complex64 __out;

                            ///////////////////
                            // Tasklet code (exp)
                            __out = exp(__inp);
                            ///////////////////

                            B[(__i0 + (24 * i))] = __out;
                        }
                    }
                    auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
                    dace::perf::report.add("timer_Map exp_map", __dace_tdiff_0_0_4.count());
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map exponent_m_50", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/exponent_m/perf");
}

DACE_EXPORTED void __program_exponent_m(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    __program_exponent_m_internal(A, B);
}

DACE_EXPORTED int __dace_init_exponent_m(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_exponent_m(dace::complex64 * __restrict__ A, dace::complex64 * __restrict__ B)
{
}

