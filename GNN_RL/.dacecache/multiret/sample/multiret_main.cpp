#include <stdlib.h>
#include "multiret.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));
  double * __restrict__ __return_0 = (double*) calloc(20, sizeof(double));
  double * __restrict__ __return_1 = (double*) calloc(20, sizeof(double));
  double * __restrict__ __return_2 = (double*) calloc(20, sizeof(double));

  __dace_init_multiret(A, __return_0, __return_1, __return_2);
  __program_multiret(A, __return_0, __return_1, __return_2);
  __dace_exit_multiret(A, __return_0, __return_1, __return_2);

  free(A);
  free(__return_0);
  free(__return_1);
  free(__return_2);
  return 0;
}
