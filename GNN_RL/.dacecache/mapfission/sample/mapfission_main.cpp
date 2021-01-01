#include <stdlib.h>
#include "mapfission.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(4, sizeof(double));
  double * __restrict__ B = (double*) calloc(2, sizeof(double));

  __dace_init_mapfission(A, B);
  __program_mapfission(A, B);
  __dace_exit_mapfission(A, B);

  free(A);
  free(B);
  return 0;
}
