#include <stdlib.h>
#include "nested_call_subarray.h"

int main(int argc, char** argv) {
  float * __restrict__ a = (float*) calloc(2, sizeof(float));
  float * __restrict__ b = (float*) calloc(2, sizeof(float));

  __dace_init_nested_call_subarray(a, b);
  __program_nested_call_subarray(a, b);
  __dace_exit_nested_call_subarray(a, b);

  free(a);
  free(b);
  return 0;
}
