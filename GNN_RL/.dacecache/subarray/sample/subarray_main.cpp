#include <stdlib.h>
#include "subarray.h"

int main(int argc, char** argv) {
  int W = 42;
  double * __restrict__ A = (double*) calloc(81, sizeof(double));
  double * __restrict__ B = (double*) calloc(81, sizeof(double));

  __dace_init_subarray(A, B, W);
  __program_subarray(A, B, W);
  __dace_exit_subarray(A, B, W);

  free(A);
  free(B);
  return 0;
}
