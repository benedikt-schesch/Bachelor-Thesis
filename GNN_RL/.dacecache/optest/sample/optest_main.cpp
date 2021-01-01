#include <stdlib.h>
#include "optest.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(25, sizeof(double));
  double * __restrict__ B = (double*) calloc(25, sizeof(double));
  double * __restrict__ C = (double*) calloc(25, sizeof(double));

  __dace_init_optest(A, B, C);
  __program_optest(A, B, C);
  __dace_exit_optest(A, B, C);

  free(A);
  free(B);
  free(C);
  return 0;
}
