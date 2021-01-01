#include <stdlib.h>
#include "customreduction.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(20, sizeof(float));
  float * __restrict__ out = (float*) calloc(1, sizeof(float));

  __dace_init_customreduction(A, out);
  __program_customreduction(A, out);
  __dace_exit_customreduction(A, out);

  free(A);
  free(out);
  return 0;
}
