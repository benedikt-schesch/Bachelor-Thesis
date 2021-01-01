#include <stdlib.h>
#include "expansion.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(3000, sizeof(float));
  int * __restrict__ rng = (int*) calloc(2, sizeof(int));

  __dace_init_expansion(A, rng);
  __program_expansion(A, rng);
  __dace_exit_expansion(A, rng);

  free(A);
  free(rng);
  return 0;
}
