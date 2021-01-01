#include <stdlib.h>
#include "symbol_inference_joint.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc((M + N), sizeof(double));
  double * __restrict__ B = (double*) calloc(((2 * M) + N), sizeof(double));

  __dace_init_symbol_inference_joint(A, B, M, N);
  __program_symbol_inference_joint(A, B, M, N);
  __dace_exit_symbol_inference_joint(A, B, M, N);

  free(A);
  free(B);
  return 0;
}
