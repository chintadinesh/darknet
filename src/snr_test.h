#include "gemm.h"
#include "dark_cuda.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdint.h>


void test_gemm(void);
void __print_mat(float * mat, int mat_len);
void __read_matrices_from_file(float *A, 
                                float *B, 
                                float *Cin, 
                                float *Cout, 
                                int M, int K, int N, 
                                int lda, int ldb, int ldc);

void compute_snr(float *A, 
                float *B, 
                float *Cin, 
                float *Cout, 
                int M, int K, int N, 
                int lda, int ldb, int ldc, int scale);

void test_gemm_matt(void);
