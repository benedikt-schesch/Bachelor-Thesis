#include <stdlib.h>
#include "nested.h"

int main(int argc, char** argv) {
  double * __restrict__ a = (double*) calloc(1, sizeof(double));
  double * __restrict__ b = (double*) calloc(1, sizeof(double));

  __dace_init_nested(a, b);
  __program_nested(a, b);
  __dace_exit_nested(a, b);

  free(a);
  free(b);
  return 0;
}
