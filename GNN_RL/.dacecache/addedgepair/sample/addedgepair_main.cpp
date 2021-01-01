#include <stdlib.h>
#include "addedgepair.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(31, sizeof(double));
  double * __restrict__ B = (double*) calloc(1, sizeof(double));

  __dace_init_addedgepair(A, B);
  __program_addedgepair(A, B);
  __dace_exit_addedgepair(A, B);

  free(A);
  free(B);
  return 0;
}
