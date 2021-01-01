#include <stdlib.h>
#include "dot_sdfg.h"

int main(int argc, char** argv) {
  int n = 42;
  double * __restrict__ _result = (double*) calloc(1, sizeof(double));
  double * __restrict__ _x = (double*) calloc(n, sizeof(double));
  double * __restrict__ _y = (double*) calloc(n, sizeof(double));

  __dace_init_dot_sdfg(_result, _x, _y, n);
  __program_dot_sdfg(_result, _x, _y, n);
  __dace_exit_dot_sdfg(_result, _x, _y, n);

  free(_result);
  free(_x);
  free(_y);
  return 0;
}
