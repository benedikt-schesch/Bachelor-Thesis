#include <stdlib.h>
#include "reduce_with_indices.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(10000, sizeof(double));
  double * __restrict__ B = (double*) calloc(1, sizeof(double));

  __dace_init_reduce_with_indices(A, B);
  __program_reduce_with_indices(A, B);
  __dace_exit_reduce_with_indices(A, B);

  free(A);
  free(B);
  return 0;
}
