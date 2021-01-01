#include <stdlib.h>
#include "myprint.h"

int main(int argc, char** argv) {
  long long M = 42;
  long long N = 42;
  float * __restrict__ input = (float*) calloc(100, sizeof(float));

  __dace_init_myprint(input, M, N);
  __program_myprint(input, M, N);
  __dace_exit_myprint(input, M, N);

  free(input);
  return 0;
}
