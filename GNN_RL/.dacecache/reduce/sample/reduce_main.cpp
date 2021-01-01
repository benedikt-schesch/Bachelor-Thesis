#include <stdlib.h>
#include "reduce.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ _in = (float*) calloc(N, sizeof(float));
  float * __restrict__ _out = (float*) calloc(1, sizeof(float));

  __dace_init_reduce(_in, _out, N);
  __program_reduce(_in, _out, N);
  __dace_exit_reduce(_in, _out, N);

  free(_in);
  free(_out);
  return 0;
}
