#include <stdlib.h>
#include "vectortypes.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(4, sizeof(float));
  float * __restrict__ B = (float*) calloc(4, sizeof(float));

  __dace_init_vectortypes(A, B);
  __program_vectortypes(A, B);
  __dace_exit_vectortypes(A, B);

  free(A);
  free(B);
  return 0;
}
