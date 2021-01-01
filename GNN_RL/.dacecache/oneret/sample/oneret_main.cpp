#include <stdlib.h>
#include "oneret.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));
  double * __restrict__ __return = (double*) calloc(20, sizeof(double));

  __dace_init_oneret(A, __return);
  __program_oneret(A, __return);
  __dace_exit_oneret(A, __return);

  free(A);
  free(__return);
  return 0;
}
