/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_cudahello_internal(double * __restrict__ V, double * __restrict__ Vout, int H, int W)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < H; i += 1) {
                for (auto j = 0; j < W; j += 1) {
                    {
                        double in_V = V[((W * i) + j)];
                        double out;

                        ///////////////////
                        // Tasklet code (multiplication)
                        out = (in_V * 2.0);
                        ///////////////////

                        Vout[((W * i) + j)] = out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map multiplication", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/cudahello/perf");
}

DACE_EXPORTED void __program_cudahello(double * __restrict__ V, double * __restrict__ Vout, int H, int W)
{
    __program_cudahello_internal(V, Vout, H, W);
}

DACE_EXPORTED int __dace_init_cudahello(double * __restrict__ V, double * __restrict__ Vout, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_cudahello(double * __restrict__ V, double * __restrict__ Vout, int H, int W)
{
}

