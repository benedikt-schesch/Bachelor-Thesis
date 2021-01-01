#include <stdlib.h>
#include "inline_chain_test_11_4.h"

int main(int argc, char** argv) {
  double * __restrict__ __tmp_14_23_in_from_1_0 = (double*) calloc(20, sizeof(double));
  double * __restrict__ __tmp_15_23_out_of_1_1 = (double*) calloc(20, sizeof(double));
  double * __restrict__ __tmp_21_23_out_of_2_1 = (double*) calloc(20, sizeof(double));

  __dace_init_inline_chain_test_11_4(__tmp_14_23_in_from_1_0, __tmp_15_23_out_of_1_1, __tmp_21_23_out_of_2_1);
  __program_inline_chain_test_11_4(__tmp_14_23_in_from_1_0, __tmp_15_23_out_of_1_1, __tmp_21_23_out_of_2_1);
  __dace_exit_inline_chain_test_11_4(__tmp_14_23_in_from_1_0, __tmp_15_23_out_of_1_1, __tmp_21_23_out_of_2_1);

  free(__tmp_14_23_in_from_1_0);
  free(__tmp_15_23_out_of_1_1);
  free(__tmp_21_23_out_of_2_1);
  return 0;
}
