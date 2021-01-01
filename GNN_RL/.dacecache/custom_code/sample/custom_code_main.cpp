#include <stdlib.h>
#include "custom_code.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(600, sizeof(double));
  double * __restrict__ B = (double*) calloc(600, sizeof(double));
  double * __restrict__ C = (double*) calloc(600, sizeof(double));

  __dace_init_custom_code(A, B, C);
  __program_custom_code(A, B, C);
  __dace_exit_custom_code(A, B, C);

  free(A);
  free(B);
  free(C);
  return 0;
}
