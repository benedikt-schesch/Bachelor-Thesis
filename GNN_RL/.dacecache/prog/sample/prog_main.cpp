#include <stdlib.h>
#include "prog.h"

int main(int argc, char** argv) {
  int W = 42;
  double * __restrict__ A = (double*) calloc(120, sizeof(double));
  double * __restrict__ stats = (double*) calloc(2, sizeof(double));

  __dace_init_prog(A, stats, W);
  __program_prog(A, stats, W);
  __dace_exit_prog(A, stats, W);

  free(A);
  free(stats);
  return 0;
}
