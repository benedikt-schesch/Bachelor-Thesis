/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_copynd_internal(float * __restrict__ A_0, float * __restrict__ A_1, float * __restrict__ A_10, float * __restrict__ A_11, float * __restrict__ A_12, float * __restrict__ A_13, float * __restrict__ A_14, float * __restrict__ A_15, float * __restrict__ A_16, float * __restrict__ A_17, float * __restrict__ A_2, float * __restrict__ A_3, float * __restrict__ A_4, float * __restrict__ A_5, float * __restrict__ A_6, float * __restrict__ A_7, float * __restrict__ A_8, float * __restrict__ A_9, int N)
{

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 5, 7>::template ConstDst<7, 1>::Copy(
                A_0 + ((6 * N) - 7), A_1, N, 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
                A_2 + ((((4 * (N * N * N)) + (N * N)) + N) + 2), A_3, (N - 1), N);
            } // End omp section
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 720>::template ConstDst<1>::Copy(
                A_4, A_5, 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
                A_6 + ((((4 * (N * N * N)) + (N * N)) + (2 * N)) + 1), A_7, (N - 1), 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 1>::template ConstSrc<1>::Copy(
                A_8, A_9 + ((((4 * (N * N * N)) + (N * N)) + N) + 2), (N - 2), (N * N));
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
                A_10, A_11 + ((((4 * (N * N * N)) + (N * N)) + (2 * N)) + 1), (N - 2), 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 4>::Dynamic::Copy(
                A_12 + ((((5 * (N * N * N)) + (2 * (N * N))) + (N * (N - 10))) + 1), A_13, (N - 5), (N * N * N), ((N - 2) * ((3 * N) - 12)), (N - 4), (N * N), ((3 * N) - 6), 3, N, (N - 2), (N - 2), 1, 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
                A_14 + ((((4 * (N * N * N)) + (N * N)) + (2 * N)) + 1), A_15, (int_ceil(N, 2) - 1), 2);
            } // End omp section
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 20, 20>::template ConstDst<40, 1>::Copy(
                A_16 + 810, A_17 + 3620, 40, 1);
            } // End omp section
        } // End omp sections
    }
}

DACE_EXPORTED void __program_copynd(float * __restrict__ A_0, float * __restrict__ A_1, float * __restrict__ A_10, float * __restrict__ A_11, float * __restrict__ A_12, float * __restrict__ A_13, float * __restrict__ A_14, float * __restrict__ A_15, float * __restrict__ A_16, float * __restrict__ A_17, float * __restrict__ A_2, float * __restrict__ A_3, float * __restrict__ A_4, float * __restrict__ A_5, float * __restrict__ A_6, float * __restrict__ A_7, float * __restrict__ A_8, float * __restrict__ A_9, int N)
{
    __program_copynd_internal(A_0, A_1, A_10, A_11, A_12, A_13, A_14, A_15, A_16, A_17, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, N);
}

DACE_EXPORTED int __dace_init_copynd(float * __restrict__ A_0, float * __restrict__ A_1, float * __restrict__ A_10, float * __restrict__ A_11, float * __restrict__ A_12, float * __restrict__ A_13, float * __restrict__ A_14, float * __restrict__ A_15, float * __restrict__ A_16, float * __restrict__ A_17, float * __restrict__ A_2, float * __restrict__ A_3, float * __restrict__ A_4, float * __restrict__ A_5, float * __restrict__ A_6, float * __restrict__ A_7, float * __restrict__ A_8, float * __restrict__ A_9, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_copynd(float * __restrict__ A_0, float * __restrict__ A_1, float * __restrict__ A_10, float * __restrict__ A_11, float * __restrict__ A_12, float * __restrict__ A_13, float * __restrict__ A_14, float * __restrict__ A_15, float * __restrict__ A_16, float * __restrict__ A_17, float * __restrict__ A_2, float * __restrict__ A_3, float * __restrict__ A_4, float * __restrict__ A_5, float * __restrict__ A_6, float * __restrict__ A_7, float * __restrict__ A_8, float * __restrict__ A_9, int N)
{
}

