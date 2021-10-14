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

int test_gemm_nn_offload();
