/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_symbol_inference_joint_internal(double * __restrict__ A, double * __restrict__ B, int M, int N)
{

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < (M + N); i += 1) {
                        {
                            double a;

                            ///////////////////
                            // Tasklet code (symbol_inference_joint_25)
                            a = N;
                            ///////////////////

                            A[i] = a;
                        }
                    }
                }
            } // End omp section
            #pragma omp section
            {
                {
                    #pragma omp parallel for
                    for (auto i = 0; i < ((2 * M) + N); i += 1) {
                        {
                            double b;

                            ///////////////////
                            // Tasklet code (symbol_inference_joint_30)
                            b = M;
                            ///////////////////

                            B[i] = b;
                        }
                    }
                }
            } // End omp section
        } // End omp sections
    }
}

DACE_EXPORTED void __program_symbol_inference_joint(double * __restrict__ A, double * __restrict__ B, int M, int N)
{
    __program_symbol_inference_joint_internal(A, B, M, N);
}

DACE_EXPORTED int __dace_init_symbol_inference_joint(double * __restrict__ A, double * __restrict__ B, int M, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_symbol_inference_joint(double * __restrict__ A, double * __restrict__ B, int M, int N)
{
}

