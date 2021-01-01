#include <stdlib.h>
#include "testprogram.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));
  double * __restrict__ __return = (double*) calloc(20, sizeof(double));

  __dace_init_testprogram(A, __return);
  __program_testprogram(A, __return);
  __dace_exit_testprogram(A, __return);

  free(A);
  free(__return);
  return 0;
}
