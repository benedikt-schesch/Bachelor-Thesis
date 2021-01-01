/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_inputs_outputs_fission_internal(double * __restrict__ in1, double * __restrict__ in2, double * __restrict__ out1, double * __restrict__ out2)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                double tmp[1]  DACE_ALIGN(64);
                {
                    double i1 = in1[i];
                    double o1;
                    double o2;

                    ///////////////////
                    // Tasklet code (t1)
                    o1 = (i1 * 2);
                    o2 = (i1 * 5);
                    ///////////////////

                    tmp[0] = o1;
                    out2[i] = o2;
                }
                {
                    double i1 = tmp[0];
                    double i2 = in2[i];
                    double o1;

                    ///////////////////
                    // Tasklet code (t2)
                    o1 = (i1 * i2);
                    ///////////////////

                    out1[i] = o1;
                }
            }
            auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
            dace::perf::report.add("timer_Map outer_fused", __dace_tdiff_0_0_7.count());
        }
    }
    dace::perf::report.save(".dacecache/inputs_outputs_fission/perf");
}

DACE_EXPORTED void __program_inputs_outputs_fission(double * __restrict__ in1, double * __restrict__ in2, double * __restrict__ out1, double * __restrict__ out2)
{
    __program_inputs_outputs_fission_internal(in1, in2, out1, out2);
}

DACE_EXPORTED int __dace_init_inputs_outputs_fission(double * __restrict__ in1, double * __restrict__ in2, double * __restrict__ out1, double * __restrict__ out2)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_inputs_outputs_fission(double * __restrict__ in1, double * __restrict__ in2, double * __restrict__ out1, double * __restrict__ out2)
{
}

