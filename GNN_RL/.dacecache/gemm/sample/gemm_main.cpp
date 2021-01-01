#include <stdlib.h>
#include "gemm.h"

int main(int argc, char** argv) {
  float alpha = 42;
  float beta = 42;
  float * __restrict__ A = (float*) calloc(576, sizeof(float));
  float * __restrict__ B = (float*) calloc(576, sizeof(float));
  float * __restrict__ C = (float*) calloc(576, sizeof(float));

  __dace_init_gemm(A, B, C, alpha, beta);
  __program_gemm(A, B, C, alpha, beta);
  __dace_exit_gemm(A, B, C, alpha, beta);

  free(A);
  free(B);
  free(C);
  return 0;
}
