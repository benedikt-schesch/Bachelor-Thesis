#include <stdlib.h>
#include "nested_loop_test.h"

int main(int argc, char** argv) {
  int * __restrict__ A = (int*) calloc(1, sizeof(int));

  __dace_init_nested_loop_test(A);
  __program_nested_loop_test(A);
  __dace_exit_nested_loop_test(A);

  free(A);
  return 0;
}
