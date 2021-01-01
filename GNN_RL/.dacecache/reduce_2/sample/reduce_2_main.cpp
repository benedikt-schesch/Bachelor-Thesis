#include <stdlib.h>
#include "reduce_2.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ _in = (double*) calloc(M, sizeof(double));
  double * __restrict__ _out = (double*) calloc(1, sizeof(double));

  __dace_init_reduce_2(_in, _out, M, N);
  __program_reduce_2(_in, _out, M, N);
  __dace_exit_reduce_2(_in, _out, M, N);

  free(_in);
  free(_out);
  return 0;
}
