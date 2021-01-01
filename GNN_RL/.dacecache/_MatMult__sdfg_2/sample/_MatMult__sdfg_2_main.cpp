#include <stdlib.h>
#include "_MatMult__sdfg_2.h"

int main(int argc, char** argv) {
  float * __restrict__ _a = (float*) calloc(1152, sizeof(float));
  float * __restrict__ _x = (float*) calloc(48, sizeof(float));
  float * __restrict__ _y = (float*) calloc(24, sizeof(float));

  __dace_init__MatMult__sdfg_2(_a, _x, _y);
  __program__MatMult__sdfg_2(_a, _x, _y);
  __dace_exit__MatMult__sdfg_2(_a, _x, _y);

  free(_a);
  free(_x);
  free(_y);
  return 0;
}
