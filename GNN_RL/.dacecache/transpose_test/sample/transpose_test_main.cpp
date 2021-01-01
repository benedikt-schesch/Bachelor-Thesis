#include <stdlib.h>
#include "transpose_test.h"

int main(int argc, char** argv) {
  float * __restrict__ C = (float*) calloc(400, sizeof(float));
  float * __restrict__ D = (float*) calloc(400, sizeof(float));

  __dace_init_transpose_test(C, D);
  __program_transpose_test(C, D);
  __dace_exit_transpose_test(C, D);

  free(C);
  free(D);
  return 0;
}
