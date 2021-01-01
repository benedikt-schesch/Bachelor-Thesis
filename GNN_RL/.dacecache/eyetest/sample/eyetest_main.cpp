#include <stdlib.h>
#include "eyetest.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ __return = (double*) calloc((N * N), sizeof(double));

  __dace_init_eyetest(__return, N);
  __program_eyetest(__return, N);
  __dace_exit_eyetest(__return, N);

  free(__return);
  return 0;
}
