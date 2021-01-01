#include <stdlib.h>
#include "writeresult.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ output = (double*) calloc(10, sizeof(double));
  double * __restrict__ values = (double*) calloc(N, sizeof(double));

  __dace_init_writeresult(output, values, N);
  __program_writeresult(output, values, N);
  __dace_exit_writeresult(output, values, N);

  free(output);
  free(values);
  return 0;
}
