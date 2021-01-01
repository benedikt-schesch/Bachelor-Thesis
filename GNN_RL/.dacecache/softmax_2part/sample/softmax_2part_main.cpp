#include <stdlib.h>
#include "softmax_2part.h"

int main(int argc, char** argv) {
  int B = 42;
  int H = 42;
  int SM = 42;
  int SN = 42;
  float * __restrict__ X_in = (float*) calloc((((B * H) * SM) * SN), sizeof(float));
  float * __restrict__ __return = (float*) calloc((((B * H) * SM) * SN), sizeof(float));

  __dace_init_softmax_2part(X_in, __return, B, H, SM, SN);
  __program_softmax_2part(X_in, __return, B, H, SM, SN);
  __dace_exit_softmax_2part(X_in, __return, B, H, SM, SN);

  free(X_in);
  free(__return);
  return 0;
}
