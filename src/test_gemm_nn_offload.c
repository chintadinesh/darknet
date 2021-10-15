#include "gemm_nn_offload.h"
#include "gemm.h"
#include "utils.h"
#include "im2col.h"
#include "dark_cuda.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdint.h>

#if defined(_OPENMP)
#include <omp.h>
#endif

#define PUT_IN_REGISTER register


extern bool save_output;
extern float maximum, minimum;
extern bool use_fx_conv;
extern bool use_cnative_round;
extern bool use_withscale_int_round;
extern bool calclate_snr_for_img;
extern int scale;

int M = 1, K = 7, N = 1, lda = 7, ldb = 1, ldc = 1; 
int ALPHA = 1;

float A[1][7] = {{0.2, 0.2, 0.2, 0.2, 0.2, 0.2, -0.2}};

float B[7][1] = { {0.4},
                {0.4},
                {0.4},
                {0.4},
                {0.4},
                {0.4},
                {0.4},
                {0.4}};

float C[1][1] = {{0}};

int test_gemm_nn_offload() {

    printf("Testing the offload function\n");

    gemm_nn_offload(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);

    return 0;
}
