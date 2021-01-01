/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void nested_state_0_1_0_4(double* A, double* B) {

    {
        
        
        {
            double a = A[0];
            double b;

            ///////////////////
            // Tasklet code (nest_subgraph_10)
            b = a;
            ///////////////////

            B[0] = b;
        }
    }
    
}

inline void nested_MapState_0_0_2(double* A, double* B) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 1; i += 1) {
                nested_state_0_1_0_4(&A[i], &B[i]);
            }
        }
    }
    
}

void __program_nest_subgraph_internal(double * __restrict__ A, double * __restrict__ B)
{

    {
        
        
        nested_MapState_0_0_2(&A[0], &B[0]);
    }
}

DACE_EXPORTED void __program_nest_subgraph(double * __restrict__ A, double * __restrict__ B)
{
    __program_nest_subgraph_internal(A, B);
}

DACE_EXPORTED int __dace_init_nest_subgraph(double * __restrict__ A, double * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nest_subgraph(double * __restrict__ A, double * __restrict__ B)
{
}

