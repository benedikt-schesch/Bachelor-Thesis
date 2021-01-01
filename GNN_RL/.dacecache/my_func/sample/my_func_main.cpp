#include <stdlib.h>
#include "my_func.h"

int main(int argc, char** argv) {
  int K = 42;
  int M = 42;
  float * __restrict__ a = (float*) calloc((K * M), sizeof(float));
  float * __restrict__ b = (float*) calloc((K * M), sizeof(float));

  __dace_init_my_func(a, b, K, M);
  __program_my_func(a, b, K, M);
  __dace_exit_my_func(a, b, K, M);

  free(a);
  free(b);
  return 0;
}
