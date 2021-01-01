#include <stdlib.h>
#include "copynd.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A_0 = (float*) calloc((N * N), sizeof(float));
  float * __restrict__ A_1 = (float*) calloc(35, sizeof(float));
  float * __restrict__ A_10 = (float*) calloc((N - 2), sizeof(float));
  float * __restrict__ A_11 = (float*) calloc((N * N * N * N), sizeof(float));
  float * __restrict__ A_12 = (float*) calloc((N * N * N * N), sizeof(float));
  float * __restrict__ A_13 = (float*) calloc((((3 * (N - 5)) * (N - 4)) * (N - 2)), sizeof(float));
  float * __restrict__ A_14 = (float*) calloc((N * N * N * N), sizeof(float));
  float * __restrict__ A_15 = (float*) calloc(((N / 2) - 1), sizeof(float));
  float * __restrict__ A_16 = (float*) calloc(1600, sizeof(float));
  float * __restrict__ A_17 = (float*) calloc(4800, sizeof(float));
  float * __restrict__ A_2 = (float*) calloc((N * N * N * N), sizeof(float));
  float * __restrict__ A_3 = (float*) calloc((N - 1), sizeof(float));
  float * __restrict__ A_4 = (float*) calloc(720, sizeof(float));
  float * __restrict__ A_5 = (float*) calloc(720, sizeof(float));
  float * __restrict__ A_6 = (float*) calloc((N * N * N * N), sizeof(float));
  float * __restrict__ A_7 = (float*) calloc((N - 1), sizeof(float));
  float * __restrict__ A_8 = (float*) calloc((N - 2), sizeof(float));
  float * __restrict__ A_9 = (float*) calloc((N * N * N * N), sizeof(float));

  __dace_init_copynd(A_0, A_1, A_10, A_11, A_12, A_13, A_14, A_15, A_16, A_17, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, N);
  __program_copynd(A_0, A_1, A_10, A_11, A_12, A_13, A_14, A_15, A_16, A_17, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, N);
  __dace_exit_copynd(A_0, A_1, A_10, A_11, A_12, A_13, A_14, A_15, A_16, A_17, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, N);

  free(A_0);
  free(A_1);
  free(A_10);
  free(A_11);
  free(A_12);
  free(A_13);
  free(A_14);
  free(A_15);
  free(A_16);
  free(A_17);
  free(A_2);
  free(A_3);
  free(A_4);
  free(A_5);
  free(A_6);
  free(A_7);
  free(A_8);
  free(A_9);
  return 0;
}
