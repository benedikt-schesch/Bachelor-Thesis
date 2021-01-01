#include <stdlib.h>
#include "ifchain.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(1, sizeof(float));

  __dace_init_ifchain(A);
  __program_ifchain(A);
  __dace_exit_ifchain(A);

  free(A);
  return 0;
}
