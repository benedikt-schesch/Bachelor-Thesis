#include <stdlib.h>
#include "transpose_sdfg.h"

int main(int argc, char** argv) {
  float * __restrict__ _inp = (float*) calloc(9, sizeof(float));
  float * __restrict__ _out = (float*) calloc(9, sizeof(float));

  __dace_init_transpose_sdfg(_inp, _out);
  __program_transpose_sdfg(_inp, _out);
  __dace_exit_transpose_sdfg(_inp, _out);

  free(_inp);
  free(_out);
  return 0;
}
