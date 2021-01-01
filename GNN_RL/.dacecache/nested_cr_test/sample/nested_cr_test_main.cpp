#include <stdlib.h>
#include "nested_cr_test.h"

int main(int argc, char** argv) {
  int * __restrict__ B = (int*) calloc(1, sizeof(int));

  __dace_init_nested_cr_test(B);
  __program_nested_cr_test(B);
  __dace_exit_nested_cr_test(B);

  free(B);
  return 0;
}
