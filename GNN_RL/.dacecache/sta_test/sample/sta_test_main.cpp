#include <stdlib.h>
#include "sta_test.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(1, sizeof(float));
  float * __restrict__ inp = (float*) calloc(1, sizeof(float));

  __dace_init_sta_test(A, inp);
  __program_sta_test(A, inp);
  __dace_exit_sta_test(A, inp);

  free(A);
  free(inp);
  return 0;
}
