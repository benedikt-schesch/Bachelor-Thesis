#include <stdlib.h>
#include "callback_with_arrays.h"

int main(int argc, char** argv) {
  void (*arrfunc)(double const *,double const *) = 42;
  int sym_0 = 42;
  int sym_1 = 42;
  int sym_2 = 42;
  double * __restrict__ in_arr = (double*) calloc(((sym_0 * sym_1) * sym_2), sizeof(double));
  double * __restrict__ out_arr = (double*) calloc(((sym_0 * sym_1) * sym_2), sizeof(double));

  __dace_init_callback_with_arrays(in_arr, out_arr, arrfunc, sym_0, sym_1, sym_2);
  __program_callback_with_arrays(in_arr, out_arr, arrfunc, sym_0, sym_1, sym_2);
  __dace_exit_callback_with_arrays(in_arr, out_arr, arrfunc, sym_0, sym_1, sym_2);

  free(in_arr);
  free(out_arr);
  return 0;
}
