/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_tovec_uneven_internal(double * __restrict__ A, int N)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 1; i < 2; i += 1) {
                {
                    double a = A[i];
                    double b;

                    ///////////////////
                    // Tasklet code (tovec_uneven_30)
                    b = (a + a);
                    ///////////////////

                    A[i] = b;
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 2; i < N; i += 2) {
                {
                    dace::vec<double, 2> a = *(dace::vec<double, 2> *)(&A[i]);
                    dace::vec<double, 2> b;

                    ///////////////////
                    // Tasklet code (tovec_uneven_30)
                    b = (a + a);
                    ///////////////////

                    *(dace::vec<double, 2> *)(&A[i]) = b;
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = ((N - ((N + 1) % 2)) + 1); i < (N + 1); i += 1) {
                {
                    double a = A[i];
                    double b;

                    ///////////////////
                    // Tasklet code (tovec_uneven_30)
                    b = (a + a);
                    ///////////////////

                    A[i] = b;
                }
            }
        }
    }
}

DACE_EXPORTED void __program_tovec_uneven(double * __restrict__ A, int N)
{
    __program_tovec_uneven_internal(A, N);
}

DACE_EXPORTED int __dace_init_tovec_uneven(double * __restrict__ A, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tovec_uneven(double * __restrict__ A, int N)
{
}

