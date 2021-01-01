#include <stdlib.h>
#include "histogram.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  unsigned char * __restrict__ A = (unsigned char*) calloc((H * W), sizeof(unsigned char));
  unsigned int * __restrict__ hist = (unsigned int*) calloc(256, sizeof(unsigned int));

  __dace_init_histogram(A, hist, H, W);
  __program_histogram(A, hist, H, W);
  __dace_exit_histogram(A, hist, H, W);

  free(A);
  free(hist);
  return 0;
}
