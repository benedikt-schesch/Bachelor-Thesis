/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void reduce_0_0_4(float* _in, float* _out) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            for (auto _i0 = 0; _i0 < 2; _i0 += 1) {
                {
                    float inp = _in[_i0];
                    float out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce(_out, out);
                }
            }
        }
    }
    
}

void __program_nested_reduction_internal(float * __restrict__ A, float * __restrict__ B)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                reduce_0_0_4(&A[(2 * i)], &B[i]);
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map mymap", __dace_tdiff_0_0_2.count());
        }
    }
    dace::perf::report.save(".dacecache/nested_reduction/perf");
}

DACE_EXPORTED void __program_nested_reduction(float * __restrict__ A, float * __restrict__ B)
{
    __program_nested_reduction_internal(A, B);
}

DACE_EXPORTED int __dace_init_nested_reduction(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_reduction(float * __restrict__ A, float * __restrict__ B)
{
}

