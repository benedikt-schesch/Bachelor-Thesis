#include <stdlib.h>
#include "matmul_delegation_test.h"

int main(int argc, char** argv) {
  float * __restrict__ matrix0 = (float*) calloc(288, sizeof(float));
  float * __restrict__ matrix1 = (float*) calloc(576, sizeof(float));
  float * __restrict__ result = (float*) calloc(1, sizeof(float));
  float * __restrict__ vector0 = (float*) calloc(48, sizeof(float));
  float * __restrict__ vector1 = (float*) calloc(24, sizeof(float));

  __dace_init_matmul_delegation_test(matrix0, matrix1, result, vector0, vector1);
  __program_matmul_delegation_test(matrix0, matrix1, result, vector0, vector1);
  __dace_exit_matmul_delegation_test(matrix0, matrix1, result, vector0, vector1);

  free(matrix0);
  free(matrix1);
  free(result);
  free(vector0);
  free(vector1);
  return 0;
}
