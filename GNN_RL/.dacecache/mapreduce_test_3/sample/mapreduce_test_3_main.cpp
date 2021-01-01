#include <stdlib.h>
#include "mapreduce_test_3.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ B = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ sum = (float*) calloc(1, sizeof(float));

  __dace_init_mapreduce_test_3(A, B, sum, H, W);
  __program_mapreduce_test_3(A, B, sum, H, W);
  __dace_exit_mapreduce_test_3(A, B, sum, H, W);

  free(A);
  free(B);
  free(sum);
  return 0;
}
