/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_indirection_internal(double * __restrict__ A, int * __restrict__ x, int M, int N)
{
    dace::perf::report.reset();
    double *__tmp0 = new double DACE_ALIGN(64)[1];
    long long j;

    {
        
        
        {
            double out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 1.0;
            ///////////////////

            __tmp0[0] = out;
        }
        {
            auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < M; __i0 += 1) {
                {
                    double __inp = __tmp0[0];
                    double __out;

                    ///////////////////
                    // Tasklet code (assign_12_4)
                    __out = __inp;
                    ///////////////////

                    A[__i0] = __out;
                }
            }
            auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
            dace::perf::report.add("timer_Map assign_12_4_map", __dace_tdiff_0_0_2.count());
        }
    }
    for (j = 1; (j < N); j = (j + 1)) {
        {
            double *____tmp1_value = new double DACE_ALIGN(64)[1];
            double *____tmp3_value = new double DACE_ALIGN(64)[1];
            double ____tmp2_value;
            
            
            {
                double* __ind___tmp1 = &A[0];
                int index_x_0 = x[(j - 1)];
                double lookup;

                ///////////////////
                // Tasklet code (Indirection)
                lookup = __ind___tmp1[index_x_0];
                ///////////////////

                ____tmp1_value[0] = lookup;
            }
            {
                double* __ind___tmp3 = &A[0];
                int index_x_0 = x[j];
                double lookup;

                ///////////////////
                // Tasklet code (Indirection)
                lookup = __ind___tmp3[index_x_0];
                ///////////////////

                ____tmp3_value[0] = lookup;
            }
            {
                double __in1 = ____tmp3_value[0];
                double __in2 = ____tmp1_value[0];
                double __out;

                ///////////////////
                // Tasklet code (augassign_14_8)
                __out = (__in1 + __in2);
                ///////////////////

                ____tmp2_value = __out;
            }
            {
                int index_x_0 = x[j];
                double lookup = ____tmp2_value;
                double* __ind___tmp2 = A;

                ///////////////////
                // Tasklet code (Indirection)
                __ind___tmp2[index_x_0] = lookup;
                ///////////////////

            }
            delete[] ____tmp1_value;
            delete[] ____tmp3_value;
        }
    }
    delete[] __tmp0;
    dace::perf::report.save(".dacecache/indirection/perf");
}

DACE_EXPORTED void __program_indirection(double * __restrict__ A, int * __restrict__ x, int M, int N)
{
    __program_indirection_internal(A, x, M, N);
}

DACE_EXPORTED int __dace_init_indirection(double * __restrict__ A, int * __restrict__ x, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_indirection(double * __restrict__ A, int * __restrict__ x, int M, int N)
{
}

