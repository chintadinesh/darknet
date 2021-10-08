
#define DTYPE int

void gemm_nn_offload(int M, int N, int K, float ALPHA,
    float *A, int lda,
    float *B, int ldb,
    float *C, int ldc);
