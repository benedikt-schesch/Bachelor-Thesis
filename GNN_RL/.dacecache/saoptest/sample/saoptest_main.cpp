#include <stdlib.h>
#include "saoptest.h"

int main(int argc, char** argv) {
  double alpha = 42;
  double * __restrict__ A = (double*) calloc(25, sizeof(double));
  double * __restrict__ B = (double*) calloc(25, sizeof(double));

  __dace_init_saoptest(A, B, alpha);
  __program_saoptest(A, B, alpha);
  __dace_exit_saoptest(A, B, alpha);

  free(A);
  free(B);
  return 0;
}
