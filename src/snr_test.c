#include "gemm.h"
#include "dark_cuda.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdint.h>


void main(int argc, char argv[]){

    gemm( TA,  TB,  M,  N,  K,  ALPHA, *A,  lda, *B,  ldb, BETA, *C,  ldc);

    return;
}
