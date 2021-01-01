/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_multiply_internal(double * __restrict__ X, double * __restrict__ Y, double * __restrict__ Z, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_6 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < int_ceil(N, 2); tile_i += 1) {
                {
                    auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
                    for (auto i = (2 * tile_i); i < (min(N, ((2 * tile_i) + 2)) - 1); i += 2) {
                        {
                            dace::vec<double, 2> x = *(dace::vec<double, 2> *)(&X[i]);
                            dace::vec<double, 2> y = *(dace::vec<double, 2> *)(&Y[i]);
                            dace::vec<double, 2> z;

                            ///////////////////
                            // Tasklet code (mult)
                            z = (y * x);
                            ///////////////////

                            *(dace::vec<double, 2> *)(&Z[i]) = z;
                        }
                    }
                    auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
                    dace::perf::report.add("timer_Map mult", __dace_tdiff_0_0_0.count());
                }
            }
            auto __dace_tend_0_0_6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_6 = __dace_tend_0_0_6 - __dace_tbegin_0_0_6;
            dace::perf::report.add("timer_Map tile_i_mult", __dace_tdiff_0_0_6.count());
        }
    }
    dace::perf::report.save(".dacecache/multiply/perf");
}

DACE_EXPORTED void __program_multiply(double * __restrict__ X, double * __restrict__ Y, double * __restrict__ Z, int N)
{
    __program_multiply_internal(X, Y, Z, N);
}

DACE_EXPORTED int __dace_init_multiply(double * __restrict__ X, double * __restrict__ Y, double * __restrict__ Z, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_multiply(double * __restrict__ X, double * __restrict__ Y, double * __restrict__ Z, int N)
{
}

