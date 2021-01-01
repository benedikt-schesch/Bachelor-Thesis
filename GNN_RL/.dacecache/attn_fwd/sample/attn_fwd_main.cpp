#include <stdlib.h>
#include "attn_fwd.h"

int main(int argc, char** argv) {
  int Qsize = 42;
  int batchSize = 42;
  int numHeads = 42;
  int projQsize = 42;
  int seqLenK = 42;
  int seqLenQ = 42;
  float * __restrict__ k = (float*) calloc(((Qsize * batchSize) * seqLenK), sizeof(float));
  float * __restrict__ out = (float*) calloc(((Qsize * batchSize) * seqLenQ), sizeof(float));
  float * __restrict__ q = (float*) calloc(((Qsize * batchSize) * seqLenQ), sizeof(float));
  float * __restrict__ v = (float*) calloc(((Qsize * batchSize) * seqLenK), sizeof(float));
  float * __restrict__ wk = (float*) calloc(((Qsize * numHeads) * projQsize), sizeof(float));
  float * __restrict__ wo = (float*) calloc(((Qsize * numHeads) * projQsize), sizeof(float));
  float * __restrict__ wq = (float*) calloc(((Qsize * numHeads) * projQsize), sizeof(float));
  float * __restrict__ wv = (float*) calloc(((Qsize * numHeads) * projQsize), sizeof(float));

  __dace_init_attn_fwd(k, out, q, v, wk, wo, wq, wv, Qsize, batchSize, numHeads, projQsize, seqLenK, seqLenQ);
  __program_attn_fwd(k, out, q, v, wk, wo, wq, wv, Qsize, batchSize, numHeads, projQsize, seqLenK, seqLenQ);
  __dace_exit_attn_fwd(k, out, q, v, wk, wo, wq, wv, Qsize, batchSize, numHeads, projQsize, seqLenK, seqLenQ);

  free(k);
  free(out);
  free(q);
  free(v);
  free(wk);
  free(wo);
  free(wq);
  free(wv);
  return 0;
}
