/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void _MatMult__sdfg_0_0_18(float* _a, float* _b, float* _c) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 24; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 24; _o1 += 1) {
                    {
                        float out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((24 * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < 24; __i2 += 1) {
                        {
                            float __a = _a[((24 * __i0) + __i2)];
                            float __b = _b[(__i1 + (24 * __i2))];
                            float __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_c + ((24 * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_gemm_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta)
{
    dace::perf::report.reset();

    {
        float *__tmp0 = new float DACE_ALIGN(64)[576];
        float *__tmp1 = new float DACE_ALIGN(64)[576];
        float *__tmp2 = new float DACE_ALIGN(64)[576];
        
        
        {
            auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    {
                        float __in2 = A[((24 * __i0) + __i1)];
                        float __in1 = alpha;
                        float __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        __tmp0[((24 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_0.count());
        }
        _MatMult__sdfg_0_0_18(&__tmp0[0], &B[0], &__tmp1[0]);
        {
            auto __dace_tbegin_0_0_8 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    {
                        float __in2 = C[((24 * __i0) + __i1)];
                        float __in1 = beta;
                        float __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        __tmp2[((24 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_8 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_8 = __dace_tend_0_0_8 - __dace_tbegin_0_0_8;
            dace::perf::report.add("timer_Map _Mult__map", __dace_tdiff_0_0_8.count());
        }
        {
            auto __dace_tbegin_0_0_14 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 24; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 24; __i1 += 1) {
                    {
                        float __in1 = __tmp1[((24 * __i0) + __i1)];
                        float __in2 = __tmp2[((24 * __i0) + __i1)];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        C[((24 * __i0) + __i1)] = __out;
                    }
                }
            }
            auto __dace_tend_0_0_14 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_14 = __dace_tend_0_0_14 - __dace_tbegin_0_0_14;
            dace::perf::report.add("timer_Map _Add__map", __dace_tdiff_0_0_14.count());
        }
        delete[] __tmp0;
        delete[] __tmp1;
        delete[] __tmp2;
    }
    dace::perf::report.save(".dacecache/gemm/perf");
}

DACE_EXPORTED void __program_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta)
{
    __program_gemm_internal(A, B, C, alpha, beta);
}

DACE_EXPORTED int __dace_init_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta)
{
}

