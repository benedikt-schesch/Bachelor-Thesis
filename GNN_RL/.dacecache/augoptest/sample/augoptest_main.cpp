#include <stdlib.h>
#include "augoptest.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(25, sizeof(double));
  double * __restrict__ B = (double*) calloc(25, sizeof(double));

  __dace_init_augoptest(A, B);
  __program_augoptest(A, B);
  __dace_exit_augoptest(A, B);

  free(A);
  free(B);
  return 0;
}
