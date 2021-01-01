#include <stdlib.h>
#include "dace_softmax.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ X_in = (float*) calloc(N, sizeof(float));
  float * __restrict__ X_out = (float*) calloc(N, sizeof(float));

  __dace_init_dace_softmax(X_in, X_out, N);
  __program_dace_softmax(X_in, X_out, N);
  __dace_exit_dace_softmax(X_in, X_out, N);

  free(X_in);
  free(X_out);
  return 0;
}
