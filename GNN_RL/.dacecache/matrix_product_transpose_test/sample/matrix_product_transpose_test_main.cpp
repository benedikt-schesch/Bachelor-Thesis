#include <stdlib.h>
#include "matrix_product_transpose_test.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(1152, sizeof(float));
  float * __restrict__ B = (float*) calloc(576, sizeof(float));
  float * __restrict__ C = (float*) calloc(288, sizeof(float));

  __dace_init_matrix_product_transpose_test(A, B, C);
  __program_matrix_product_transpose_test(A, B, C);
  __dace_exit_matrix_product_transpose_test(A, B, C);

  free(A);
  free(B);
  free(C);
  return 0;
}
