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

// http://users.ece.utexas.edu/~gerstl/ece382m_f21/labs/lab1/fp2fx.cpp
int __roundup(float fp_number) {
    //if(fp_number > maximum) maximum = fp_number;
    //if(fp_number < minimum) minimum = fp_number;

	DTYPE fx_number	=	(DTYPE)fp_number;
    //printf("Hello\n");

	if(fp_number-fx_number>=0.5)	fx_number++;

	return	fx_number;
}


void gemm_nn_offload(int M, int N, int K, float ALPHA,
    float *A, int lda,
    float *B, int ldb,
    float *C, int ldc)


{
    int i, j, k;

    /* Uncomment for floating point computations
    //printf("Hello\n");
    for (i = 0; i < M; ++i) {
        for (k = 0; k < K; ++k) {
            PUT_IN_REGISTER float A_PART = ALPHA * A[i * lda + k];

            for (j = 0; j < N; ++j) {
                C[i*ldc + j] += A_PART*B[k*ldb + j];
            }

            // // SSE
            //printf("Hello\n");
            __m128 a128, b128, c128, result128;    // SSE
            a128 = _mm_set1_ps(A_PART);
            for (j = 0; j < N - 4; j += 4) {
            b128 = _mm_loadu_ps(&B[k*ldb + j]);
            c128 = _mm_loadu_ps(&C[i*ldc + j]);
            //result128 = _mm_fmadd_ps(a128, b128, c128);
            result128 = _mm_mul_ps(a128, b128);
            result128 = _mm_add_ps(result128, c128);
            _mm_storeu_ps(&C[i*ldc + j], result128);
            }

            int prev_end = (N % 4 == 0) ? (N - 4) : (N / 4) * 4;
            for (j = prev_end; j < N; ++j){
            C[i*ldc + j] += A_PART*B[k*ldb + j];
            }
            


        }
    }
    */

    //Uncomment for int point computations

    if(use_fx_conv){ 
        //TODO: adjust scale intelligently
        //int scale = 1;

        // convert ALPHA into int here
        //PUT_IN_REGISTER int AlPHA = __roundup(ALPHA * (1 << scale));
        //int tmp_k_mult, tmp_j_mult;
        //int tmp_k_div; 

        DTYPE ALPHA_con = __roundup(ALPHA * (1 << scale));
        //printf("ALPHA = %d\n", ALPHA_con);

        for (i = 0; i < M; ++i) {
            for (k = 0; k < K; ++k) {
                //tmp_k_mult = ((ALPHA_con * __roundup(A[i * lda + k] * (1 << scale))) >> scale);

                //tmp_k_div = (int)(tmp_k_mult / (1 << scale));
                //printf("tmp_k_div = %d\n", tmp_k_div);

                //PUT_IN_REGISTER int A_PART = tmp_k_mult; 

                PUT_IN_REGISTER int A_PART = ((ALPHA_con * __roundup(A[i * lda + k] * (1 << scale))) >> scale);

                //printf("A_PART num = %d\n", tmp_k_mult);

                #pragma omp parallel for
                for (j = 0; j < N; ++j) {
                    //DTYPE res =  A_PART * __roundup(B[k*ldb + j] * (1 << scale));

                    //printf("B_PART num = %d\n", tmp_j_mult);

                    //float calc_num =((float)tmp_j_mult) / (1 << scale); 
                    C[i*ldc + j] += ((float)((A_PART *
                                            __roundup( B[k*ldb + j] * (1 << scale))) 
                                            >> scale))    /  ( 1 << scale);

                    //printf("Calc num = %10.10f\n", calc_num);
                }
            }
        }
    }
    else if(use_withscale_int_round){
      PUT_IN_REGISTER DTYPE SCALE_NUM = (1 << scale);
      PUT_IN_REGISTER DTYPE ALPHA_con = (int)(ALPHA * SCALE_NUM);
	
        //printf("ALPHA = %d\n", ALPHA_con);

        // M=1 for many cases, there is no need for this
        //#pragma omp parallel for
        for (i = 0; i < M; ++i) {

            // experimenting without the outer pragma
            #pragma omp parallel for
            for (k = 0; k < K; ++k) {
                //tmp_k_mult = ((ALPHA_con * round(A[i * lda + k] * (1 << scale))) >> scale);

                //tmp_k_div = (int)(tmp_k_mult / (1 << scale));
                //printf("tmp_k_div = %d\n", tmp_k_div);

                //PUT_IN_REGISTER int A_PART = tmp_k_mult; 

                //PUT_IN_REGISTER int A_PART 
                // = ((ALPHA_con * (int)(A[i * lda + k] * SCALE_NUM)) >> scale);

                // converting alpha before hand
                // PUT_IN_REGISTER int A_PART 
                // 	= ((ALPHA * (DTYPE)(A[i * lda + k] * SCALE_NUM)) >> scale);
                // Sincw we already know that alpha is always one
                PUT_IN_REGISTER DTYPE A_PART 
                    = (ALPHA_con * (int)(A[i * lda + k] * SCALE_NUM))
                          >> scale;

                //printf("A_PART num = %d\n", tmp_k_mult);

                #pragma omp parallel for
                for (j = 0; j < N; ++j) {
                    //DTYPE res =  A_PART * round(B[k*ldb + j] * (1 << scale));

                    //printf("B_PART num = %d\n", tmp_j_mult);

                    //float calc_num =((float)tmp_j_mult) / (1 << scale); 

                    // remember, we can not resolve the last floating point
                    // division. If we bitshift before floating point

                    // experiment with not converting back to float but just
                    // bit shifting

                    // debug print to ensure that this code block is executed
                    // printf("Hello use_withscale_int_round\n");
                    C[i*ldc + j] 
                        += ( (float)(
                          (A_PART * (int)(B[k*ldb + j] * SCALE_NUM)) 
                                >> scale))
                                  / SCALE_NUM;
                                                                   


                    /*
                    mAP drops to 25% when this method is used
                    C[i*ldc + j] 
                        += (A_PART     *   (int)(B[k*ldb + j] * (1 << scale))) >> (2*scale);
                    */                                              


                    //printf("Calc num = %10.10f\n", calc_num);
                }
            }
        }
    }
    else if(use_cnative_round){
        //TODO: adjust scale intelligently
        //int scale = 1;

        // convert ALPHA into int here
        //PUT_IN_REGISTER int AlPHA = round(ALPHA * (1 << scale));
        //int tmp_k_mult, tmp_j_mult;
        //int tmp_k_div; 

        //DTYPE ALPHA_con = round(ALPHA);
        //printf("ALPHA = %d\n", ALPHA_con);

        DTYPE ALPHA_con = (DTYPE)(ALPHA);

        for (i = 0; i < M; ++i) {
            for (k = 0; k < K; ++k) {
                //tmp_k_mult = ((ALPHA_con * round(A[i * lda + k] * (1 << scale))) >> scale);

                //tmp_k_div = (int)(tmp_k_mult / (1 << scale));
                //printf("tmp_k_div = %d\n", tmp_k_div);

                //PUT_IN_REGISTER int A_PART = tmp_k_mult; 

                PUT_IN_REGISTER int A_PART = ALPHA_con * (DTYPE)(A[i * lda + k]);

                //printf("A_PART num = %d\n", tmp_k_mult);

                #pragma omp parallel for
                for (j = 0; j < N; ++j) {
                    //DTYPE res =  A_PART * round(B[k*ldb + j] * (1 << scale));

                    //printf("B_PART num = %d\n", tmp_j_mult);

                    //float calc_num =((float)tmp_j_mult) / (1 << scale); 
                    C[i*ldc + j] += (A_PART * (DTYPE)(B[k*ldb + j]));

                    //printf("Calc num = %10.10f\n", calc_num);
                }
            }
        }
    }
    else{
        for (i = 0; i < M; ++i) {
            for (k = 0; k < K; ++k) {
                PUT_IN_REGISTER float A_PART = ALPHA * A[i * lda + k];

                //printf("Hello\n");

                for (j = 0; j < N; ++j) {
                    C[i*ldc + j] += A_PART*B[k*ldb + j];
                }
            }
        }
    }

    return;
}
