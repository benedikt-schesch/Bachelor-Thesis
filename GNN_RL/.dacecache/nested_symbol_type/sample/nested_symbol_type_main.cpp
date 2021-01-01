#include <stdlib.h>
#include "nested_symbol_type.h"

int main(int argc, char** argv) {
  float s = 42;
  float * __restrict__ data = (float*) calloc(1, sizeof(float));

  __dace_init_nested_symbol_type(data, s);
  __program_nested_symbol_type(data, s);
  __dace_exit_nested_symbol_type(data, s);

  free(data);
  return 0;
}
