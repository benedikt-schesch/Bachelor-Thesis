#include <stdlib.h>
#include "augdivtest.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(25, sizeof(double));
  double * __restrict__ B = (double*) calloc(25, sizeof(double));

  __dace_init_augdivtest(A, B);
  __program_augdivtest(A, B);
  __dace_exit_augdivtest(A, B);

  free(A);
  free(B);
  return 0;
}
