#include <stdlib.h>
#include "computation.h"

int main(int argc, char** argv) {
  double * __restrict__ a = (double*) calloc(600, sizeof(double));
  double * __restrict__ b = (double*) calloc(600, sizeof(double));

  __dace_init_computation(a, b);
  __program_computation(a, b);
  __dace_exit_computation(a, b);

  free(a);
  free(b);
  return 0;
}
