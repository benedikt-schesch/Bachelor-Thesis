#include <stdlib.h>
#include "_MatMult__sdfg_1.h"

int main(int argc, char** argv) {
  float * __restrict__ _a = (float*) calloc(288, sizeof(float));
  float * __restrict__ _b = (float*) calloc(576, sizeof(float));
  float * __restrict__ _c = (float*) calloc(1152, sizeof(float));

  __dace_init__MatMult__sdfg_1(_a, _b, _c);
  __program__MatMult__sdfg_1(_a, _b, _c);
  __dace_exit__MatMult__sdfg_1(_a, _b, _c);

  free(_a);
  free(_b);
  free(_c);
  return 0;
}
