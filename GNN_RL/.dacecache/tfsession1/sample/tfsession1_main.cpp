#include <stdlib.h>
#include "tfsession1.h"

int main(int argc, char** argv) {
  int * __restrict__ Const_0 = (int*) calloc(18, sizeof(int));
  int * __restrict__ Slice_2_0 = (int*) calloc(6, sizeof(int));

  __dace_init_tfsession1(Const_0, Slice_2_0);
  __program_tfsession1(Const_0, Slice_2_0);
  __dace_exit_tfsession1(Const_0, Slice_2_0);

  free(Const_0);
  free(Slice_2_0);
  return 0;
}
