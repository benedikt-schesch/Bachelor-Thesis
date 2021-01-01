#include <stdlib.h>
#include "tovec_sym.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ x = (float*) calloc(N, sizeof(float));
  float * __restrict__ y = (float*) calloc(N, sizeof(float));
  float * __restrict__ z = (float*) calloc(N, sizeof(float));

  __dace_init_tovec_sym(x, y, z, N);
  __program_tovec_sym(x, y, z, N);
  __dace_exit_tovec_sym(x, y, z, N);

  free(x);
  free(y);
  free(z);
  return 0;
}
