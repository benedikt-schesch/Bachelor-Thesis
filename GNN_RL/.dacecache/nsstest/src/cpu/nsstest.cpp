/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void nested_0_0_1(double* a, double* b) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 1; i += 1) {
                {
                    double inp = a[i];
                    double out;

                    ///////////////////
                    // Tasklet code (m)
                    out = (inp * 5.0);
                    ///////////////////

                    b[i] = out;
                }
            }
        }
    }
    
}

void __program_nsstest_internal(double * __restrict__ A)
{

    {
        
        
        nested_0_0_1(&A[1], &A[0]);
    }
}

DACE_EXPORTED void __program_nsstest(double * __restrict__ A)
{
    __program_nsstest_internal(A);
}

DACE_EXPORTED int __dace_init_nsstest(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nsstest(double * __restrict__ A)
{
}

