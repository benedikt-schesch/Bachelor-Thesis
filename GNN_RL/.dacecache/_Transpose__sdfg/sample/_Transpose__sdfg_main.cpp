#include <stdlib.h>
#include "_Transpose__sdfg.h"

int main(int argc, char** argv) {
  float * __restrict__ _inp = (float*) calloc(576, sizeof(float));
  float * __restrict__ _out = (float*) calloc(576, sizeof(float));

  __dace_init__Transpose__sdfg(_inp, _out);
  __program__Transpose__sdfg(_inp, _out);
  __dace_exit__Transpose__sdfg(_inp, _out);

  free(_inp);
  free(_out);
  return 0;
}
