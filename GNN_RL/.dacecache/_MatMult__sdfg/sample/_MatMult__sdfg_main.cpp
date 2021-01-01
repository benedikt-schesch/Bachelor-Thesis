#include <stdlib.h>
#include "_MatMult__sdfg.h"

int main(int argc, char** argv) {
  float * __restrict__ _result = (float*) calloc(1, sizeof(float));
  float * __restrict__ _x = (float*) calloc(24, sizeof(float));
  float * __restrict__ _y = (float*) calloc(24, sizeof(float));

  __dace_init__MatMult__sdfg(_result, _x, _y);
  __program__MatMult__sdfg(_result, _x, _y);
  __dace_exit__MatMult__sdfg(_result, _x, _y);

  free(_result);
  free(_x);
  free(_y);
  return 0;
}
