/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_op_internal(float * __restrict__ A, float * __restrict__ __return, int N)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < N; __i0 += 1) {
                for (auto __i1 = 0; __i1 < N; __i1 += 1) {
                    {
                        float __in1 = A[((N * __i0) + __i1)];
                        float __in2 = A[((N * __i0) + __i1)];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        __return[((N * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map _Add__map", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/op/perf");
}

DACE_EXPORTED void __program_op(float * __restrict__ A, float * __restrict__ __return, int N)
{
    __program_op_internal(A, __return, N);
}

DACE_EXPORTED int __dace_init_op(float * __restrict__ A, float * __restrict__ __return, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_op(float * __restrict__ A, float * __restrict__ __return, int N)
{
}

