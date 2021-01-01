#include <stdlib.h>
#include "einsumtest.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(10000, sizeof(double));
  double * __restrict__ B = (double*) calloc(10000, sizeof(double));
  double * __restrict__ C = (double*) calloc(10000, sizeof(double));
  double * __restrict__ D = (double*) calloc(10000, sizeof(double));
  double * __restrict__ E = (double*) calloc(10000, sizeof(double));
  double * __restrict__ __return = (double*) calloc(1, sizeof(double));

  __dace_init_einsumtest(A, B, C, D, E, __return);
  __program_einsumtest(A, B, C, D, E, __return);
  __dace_exit_einsumtest(A, B, C, D, E, __return);

  free(A);
  free(B);
  free(C);
  free(D);
  free(E);
  free(__return);
  return 0;
}
