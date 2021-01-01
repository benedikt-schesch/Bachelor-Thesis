#include <stdlib.h>
#include "foo123.h"

int main(int argc, char** argv) {
  float * __restrict__ a = (float*) calloc(2, sizeof(float));
  float * __restrict__ b = (float*) calloc(2, sizeof(float));

  __dace_init_foo123(a, b);
  __program_foo123(a, b);
  __dace_exit_foo123(a, b);

  free(a);
  free(b);
  return 0;
}
