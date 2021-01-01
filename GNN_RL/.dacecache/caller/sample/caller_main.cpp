#include <stdlib.h>
#include "caller.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(4, sizeof(float));

  __dace_init_caller(A);
  __program_caller(A);
  __dace_exit_caller(A);

  free(A);
  return 0;
}
