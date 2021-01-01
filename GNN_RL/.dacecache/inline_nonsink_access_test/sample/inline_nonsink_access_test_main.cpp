#include <stdlib.h>
#include "inline_nonsink_access_test.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(1, sizeof(float));
  float * __restrict__ B = (float*) calloc(1, sizeof(float));

  __dace_init_inline_nonsink_access_test(A, B);
  __program_inline_nonsink_access_test(A, B);
  __dace_exit_inline_nonsink_access_test(A, B);

  free(A);
  free(B);
  return 0;
}
