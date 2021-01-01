/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void my_assign_0_0_4(float* X_in, float* X_out, int N) {

    {
        
        

        dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
        X_in, X_out, N, 1);
    }
    
}

void __program_my_func_internal(float * __restrict__ a, float * __restrict__ b, int K, int M)
{
    dace::perf::report.reset();

    {
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto j = 0; j < M; j += 1) {
                my_assign_0_0_4(&b[(K * j)], &a[(K * j)], K);
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map my_func_18", __dace_tdiff_0_0_0.count());
        }
    }
    dace::perf::report.save(".dacecache/my_func/perf");
}

DACE_EXPORTED void __program_my_func(float * __restrict__ a, float * __restrict__ b, int K, int M)
{
    __program_my_func_internal(a, b, K, M);
}

DACE_EXPORTED int __dace_init_my_func(float * __restrict__ a, float * __restrict__ b, int K, int M)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_my_func(float * __restrict__ a, float * __restrict__ b, int K, int M)
{
}

