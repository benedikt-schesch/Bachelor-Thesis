/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_tovec_sym_internal(float * __restrict__ x, float * __restrict__ y, float * __restrict__ z, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < (N - 3); i += 4) {
                {
                    dace::vec<float, 4> xx = *(dace::vec<float, 4> *)(&x[i]);
                    dace::vec<float, 4> yy = *(dace::vec<float, 4> *)(&y[i]);
                    dace::vec<float, 4> zz = *(dace::vec<float, 4> *)(&z[i]);
                    dace::vec<float, 4> out;

                    ///////////////////
                    // Tasklet code (sum)
                    out = ((xx + yy) + zz);
                    ///////////////////

                    *(dace::vec<float, 4> *)(&z[i]) = out;
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map sum", __dace_tdiff_0_0_0.count());
        }
        {
            auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = (N - (N % 4)); i < N; i += 1) {
                {
                    float xx = x[i];
                    float yy = y[i];
                    float zz = z[i];
                    float out;

                    ///////////////////
                    // Tasklet code (sum)
                    out = ((xx + yy) + zz);
                    ///////////////////

                    z[i] = out;
                }
            }
            auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
            dace::perf::report.add("timer_Map sum", __dace_tdiff_0_0_7.count());
        }
    }
    dace::perf::report.save(".dacecache/tovec_sym/perf");
}

DACE_EXPORTED void __program_tovec_sym(float * __restrict__ x, float * __restrict__ y, float * __restrict__ z, int N)
{
    __program_tovec_sym_internal(x, y, z, N);
}

DACE_EXPORTED int __dace_init_tovec_sym(float * __restrict__ x, float * __restrict__ y, float * __restrict__ z, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tovec_sym(float * __restrict__ x, float * __restrict__ y, float * __restrict__ z, int N)
{
}

