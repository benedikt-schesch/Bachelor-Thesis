/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

namespace dace { namespace perf { Report report; } }
void __program_slowmm_internal(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    dace::perf::report.reset();
    long long t;

    for (t = 0; (t < 20); t = (t + 1)) {
        {
            
            
            {
                #pragma omp parallel for
                for (auto i = 0; i < N; i += 1) {
                    for (auto j = 0; j < N; j += 1) {
                        for (auto k = 0; k < N; k += 1) {
                            {
                                double a = A[((N * i) + k)];
                                double b = B[((N * k) + j)];
                                double c;

                                ///////////////////
                                // Tasklet code (mult)
                                c = (a * b);
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(C + ((N * i) + j), c);
                            }
                        }
                    }
                }
            }
        }
    }
    dace::perf::report.save(".dacecache/slowmm/perf");
}

DACE_EXPORTED void __program_slowmm(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    __program_slowmm_internal(A, B, C, N);
}

DACE_EXPORTED int __dace_init_slowmm(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_slowmm(double * __restrict__ A, double * __restrict__ B, double * __restrict__ C, int N)
{
}

