#include <stdlib.h>
#include "raw_prog.h"

int main(int argc, char** argv) {
  int W = 42;
  double * __restrict__ A = (double*) calloc(3, sizeof(double));
  double * __restrict__ B = (double*) calloc(3, sizeof(double));

  __dace_init_raw_prog(A, B, W);
  __program_raw_prog(A, B, W);
  __dace_exit_raw_prog(A, B, W);

  free(A);
  free(B);
  return 0;
}
