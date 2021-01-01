#include <stdlib.h>
#include "plus_1.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ X_in = (float*) calloc(N, sizeof(float));
  float * __restrict__ X_out = (float*) calloc(N, sizeof(float));
  int * __restrict__ num = (int*) calloc(1, sizeof(int));

  __dace_init_plus_1(X_in, X_out, num, N);
  __program_plus_1(X_in, X_out, num, N);
  __dace_exit_plus_1(X_in, X_out, num, N);

  free(X_in);
  free(X_out);
  free(num);
  return 0;
}
