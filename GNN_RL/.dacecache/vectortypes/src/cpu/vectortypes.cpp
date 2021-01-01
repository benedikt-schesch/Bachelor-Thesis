/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_vectortypes_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            dace::vec<float, 2> a = *(dace::vec<float, 2> *)(&A[0]);
            dace::vec<float, 2> b;

            ///////////////////
            // Tasklet code (something)
            b = (a * 2);
            ///////////////////

            *(dace::vec<float, 2> *)(&B[0]) = b;
        }
        {
            dace::vec<float, 2> a = *(dace::vec<float, 2> *)(&A[2]);
            dace::vec<float, 2> b;

            ///////////////////
            // Tasklet code (something)
            b = (a * 2);
            ///////////////////

            *(dace::vec<float, 2> *)(&B[2]) = b;
        }
    }
}

DACE_EXPORTED void __program_vectortypes(float * __restrict__ A, float * __restrict__ B)
{
    __program_vectortypes_internal(A, B);
}

DACE_EXPORTED int __dace_init_vectortypes(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_vectortypes(float * __restrict__ A, float * __restrict__ B)
{
}

