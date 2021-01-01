#include <stdlib.h>
#include "sredtest.h"

int main(int argc, char** argv) {
  vec3d * __restrict__ A = (vec3d*) calloc(1, sizeof(vec3d));

  __dace_init_sredtest(A);
  __program_sredtest(A);
  __dace_exit_sredtest(A);

  free(A);
  return 0;
}
