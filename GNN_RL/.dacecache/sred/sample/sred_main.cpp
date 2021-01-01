#include <stdlib.h>
#include "sred.h"

int main(int argc, char** argv) {
  vec3d * __restrict__ A = (vec3d*) calloc(1, sizeof(vec3d));

  __dace_init_sred(A);
  __program_sred(A);
  __dace_exit_sred(A);

  free(A);
  return 0;
}
