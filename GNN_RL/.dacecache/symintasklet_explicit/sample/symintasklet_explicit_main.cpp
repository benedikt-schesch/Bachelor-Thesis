#include <stdlib.h>
#include "symintasklet_explicit.h"

int main(int argc, char** argv) {
  float value = 42;
  float * __restrict__ out = (float*) calloc(1, sizeof(float));

  __dace_init_symintasklet_explicit(out, value);
  __program_symintasklet_explicit(out, value);
  __dace_exit_symintasklet_explicit(out, value);

  free(out);
  return 0;
}
