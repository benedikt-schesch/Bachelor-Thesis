#include <stdlib.h>
#include "tlstream.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ ga = (float*) calloc(N, sizeof(float));

  __dace_init_tlstream(ga, N);
  __program_tlstream(ga, N);
  __dace_exit_tlstream(ga, N);

  free(ga);
  return 0;
}
