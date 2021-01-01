#include <stdlib.h>
#include "test2.h"

int main(int argc, char** argv) {
  float * __restrict__ C = (float*) calloc(1, sizeof(float));
  float * __restrict__ E = (float*) calloc(1, sizeof(float));
  float * __restrict__ F = (float*) calloc(1, sizeof(float));

  __dace_init_test2(C, E, F);
  __program_test2(C, E, F);
  __dace_exit_test2(C, E, F);

  free(C);
  free(E);
  free(F);
  return 0;
}
