#include <stdlib.h>
#include "op.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc((N * N), sizeof(float));
  float * __restrict__ __return = (float*) calloc((N * N), sizeof(float));

  __dace_init_op(A, __return, N);
  __program_op(A, __return, N);
  __dace_exit_op(A, __return, N);

  free(A);
  free(__return);
  return 0;
}
