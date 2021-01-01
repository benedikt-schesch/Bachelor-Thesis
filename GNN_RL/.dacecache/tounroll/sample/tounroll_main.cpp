#include <stdlib.h>
#include "tounroll.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));
  double * __restrict__ B = (double*) calloc(20, sizeof(double));

  __dace_init_tounroll(A, B);
  __program_tounroll(A, B);
  __dace_exit_tounroll(A, B);

  free(A);
  free(B);
  return 0;
}
