/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_control_flow_test_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ tol, int H, int W)
{
    dace::perf::report.reset();
    long long i;

    if ((tol[0] < 4)) {
        goto __state_0_guard;
    }
    if ((! (tol[0] < 4))) {
        goto __state_0_if_guard_9;
    }
    __state_0_guard:;
    if ((tol[0] < 4)) {
        goto __state_0_s13_12;
    }
    if ((! (tol[0] < 4))) {
        goto __state_0_endif_10;
    }
    __state_0_if_guard_9:;
    if ((tol[0] <= 5)) {
        goto __state_0_s22_8;
    }
    if ((! (tol[0] <= 5))) {
        goto __state_0_if_guard_14;
    }
    __state_0_s13_12:;
    {
        
        
        {
            auto __dace_tbegin_0_1_6 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto tile_i = 0; tile_i < W; tile_i += 4) {
                {
                    for (auto i = tile_i; i < (min((W - 1), (tile_i + 3)) + 1); i += 1) {
                        {
                            float a = A[i];
                            float b;
                            float t;

                            ///////////////////
                            // Tasklet code (something)
                            b = a;
                            t = (a * a);
                            ///////////////////

                            B[i] = b;
                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(tol, t);
                        }
                    }
                }
            }
            auto __dace_tend_0_1_6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_6 = __dace_tend_0_1_6 - __dace_tbegin_0_1_6;
            dace::perf::report.add("timer_Map something", __dace_tdiff_0_1_6.count());
        }
    }
    goto __state_0_guard;
    __state_0_endif_10:;
    goto __state_exit_0_sdfg;
    __state_0_s22_8:;
    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    float a = A[i];
                    float b;

                    ///////////////////
                    // Tasklet code (something)
                    b = a;
                    ///////////////////

                    B[i] = b;
                }
            }
        }
    }
    goto __state_0_endif_10;
    __state_0_if_guard_14:;
    if ((tol[0] <= 6)) {
        goto __state_0_s29_8;
    }
    if ((! (tol[0] <= 6))) {
        i = 0;
        goto __state_0_guard_22;
    }
    __state_0_s29_8:;
    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < W; i += 1) {
                {
                    float a = A[i];
                    float b;

                    ///////////////////
                    // Tasklet code (something)
                    b = a;
                    ///////////////////

                    B[i] = b;
                }
            }
        }
    }
    goto __state_0_endif_10;
    __state_0_guard_22:;
    if ((i < W)) {
        goto __state_0_s37_12;
    }
    if ((! (i < W))) {
        goto __state_0_endif_10;
    }
    __state_0_s37_12:;
    {
        
        
        {
            #pragma omp parallel for
            for (auto j = 0; j < W; j += 1) {
                {
                    float a = A[j];
                    float b;

                    ///////////////////
                    // Tasklet code (something)
                    b = a;
                    ///////////////////

                    B[j] = b;
                }
            }
        }
    }
    i = (i + 1);
    goto __state_0_guard_22;
    __state_exit_0_sdfg:;
    dace::perf::report.save(".dacecache/control_flow_test/perf");
}

DACE_EXPORTED void __program_control_flow_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ tol, int H, int W)
{
    __program_control_flow_test_internal(A, B, tol, H, W);
}

DACE_EXPORTED int __dace_init_control_flow_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ tol, int H, int W)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_control_flow_test(float * __restrict__ A, float * __restrict__ B, float * __restrict__ tol, int H, int W)
{
}

