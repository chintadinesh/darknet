#include "gemm.h"
#include "dark_cuda.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdint.h>

#include "snr_test.h"

// reading one million characters from the file at onece
#define MAX_LINE_LENGTH 100000000

extern bool use_fx_conv;
extern int scale;


void test_gemm(void){
    float A[2][4] = {{0.1, 0.1, 0.1, 0.1}, {0.1, 0.1, 0.1, 0.1}};
    float B[4][2] = {{0.1, 0.1}, {0.1, 0.1}, {0.1, 0.1}, {0.1, 0.1}};
    float C[2][2] = {{0, 0}, {0, 0}};  

    int TA = 0;
    int TB = 0;

    int M = 2;
    int N = 2;
    int K = 4;

    int lda = 4;
    int ldb = 2; 
    int ldc = 2;

    int ALPHA = 1;
    int BETA = 1;

    gemm( TA,  TB,  M,  N,  K,  ALPHA, *A,  lda, *B,  ldb, BETA, *C,  ldc);

    printf("Output matrix:\n [[%9.6f, %9.6f],\n  [%9.6f, %9.6f]]\n", 
        C[0][0], C[0][1], C[1][0], C[1][1]);

    return;
}

void __print_mat(float * mat, int mat_len){
    printf("Printing the array: ");
    for (int i = 0; i< mat_len; i++)
        printf("%0.6f ", mat[i]);
    printf("\n");

    return;
}


int __read_mat(float * mat, char * str){
    float num;
    char * lPtr;
    int mat_counter = 0;
    
    if( !(lPtr = strtok( (str + 1), "\t\n ," ) ) ) 
            return mat_counter;

    do{
        num = atof(lPtr);
        mat[mat_counter++] = num;
    } while((lPtr = strtok( NULL, "\t\n ," ) ) );

    return mat_counter;
}

int __read_mat_checked(float * mat, char * pLine, int expected_len){
    int a_len = __read_mat(mat, pLine);
    a_len--;
    printf("[DEBUG] Expected_length = %d, read_length = %d\n", expected_len, a_len);
    if(a_len != expected_len){
        printf("[ERROR] Failed to read complete matrix. Here is what that is read:\n");
        __print_mat(mat, a_len);
    }

    return a_len;
}

    
void __read_matrices_from_file(float *A, 
                                float *B, 
                                float *Cin, 
                                float *Cout, 
                                int M, int K, int N, 
                                int lda, int ldb, int ldc){

    // be careful, we are hardcoding the file
    
    char* fl_name = "src/matlab/testbench.m";
    FILE * fp = fopen(fl_name, "r");

    if(!fp){
        printf("[FATAL] Unable to read the file, %s\n", fl_name);
        exit(1);
    }

    char *pLine = (char*)malloc(sizeof(char)*MAX_LINE_LENGTH); 

    int line_number = 0;
    while(fgets( pLine, MAX_LINE_LENGTH, fp )) {
        //printf("[DEBUG] Read line: %s\n", pLine);

        if(line_number == 7){ //matrix A
            int a_len_read = __read_mat_checked(A, pLine, M*lda);
            printf("[DEBUG] Read %d nums for A\n", a_len_read);
        }
        else if (line_number == 10){ // matrix B
            int b_len_read = __read_mat_checked(B, pLine, K*ldb);
            printf("[DEBUG] Read %d nums for B\n", b_len_read);
        }
        else if (line_number == 13){ // matric Cin
            int c_in_len_read = __read_mat_checked(Cin, pLine, M*ldc);
            printf("[DEBUG] Read %d nums for Cin\n", c_in_len_read);
        }
        else if (line_number == 16){ // matrix Cout
            int c_out_len_read = __read_mat_checked(Cout, pLine, M*ldc);
            printf("[DEBUG] Read %d lines for Cout\n", c_out_len_read);
        }

        line_number++;
    }

    return;
}
    
void compute_snr(float *A, 
                float *B, 
                float *Cin, 
                float *Cout, 
                int M, int K, int N, 
                int lda, int ldb, int ldc, int scale){

    printf("[DEBUG] Reinitilizing the Cin matrix\n");

    for(int i = 0; i < M; i++){
        for(int j=0; j < N; j++) {
            Cin[i*M + j] = 0;
        }
    }


    printf("[DEBUG] Executing gemm operation\n");

    gemm_cpu( 0,  0,  M,  N,  K,  1, A,  lda, B,  ldb, 1, Cin,  ldc);

    // We set this global variable to control whether fixed point conversions
    // now let us calculate the snr

    double nums_sum = 0;
    double diff_sum = 0;
    for(int i = 0; i < M; i++){
        for(int j=0; j < N; j++) {
            nums_sum += pow(Cout[i*M + j], 2);
            diff_sum += pow((Cout[i*M +j] - Cin[i*M + j]), 2);
            //printf("E = %4.6f, C = %4.6f, s = %4.6f, d = %4.6f\n", 
            //        Cout[i*M + j], Cin[i*M + j], nums_sum, diff_sum);
        }
    }

    float snr = 10 * log(nums_sum) - 10*log(diff_sum);
    printf("[RESULT] nums_sum = %10.6f\n", nums_sum);
    printf("[RESULT] diff_sum = %10.6f\n", diff_sum);
    printf("[RESULT] scale = %d; snr = %4.6f\n", scale, snr);
    printf("\n");

    return;
}

void test_gemm_matt(void){
    //Hardcoded:
    // 1. matrix dimensions of
    // 2. line numbers in which the data is present

    int M = 1;
    int N = 676;
    int K = 256;

    int lda = K;
    int ldb = N; 
    int ldc = N;

    printf("[DEBUG] Allocating memory for matrices\n");
    float *A = (float *) malloc(sizeof(float)*M*lda);
    float *B = (float *) malloc(sizeof(float)*K*ldb);
    float *Cin = (float *) malloc(sizeof(float)*M*ldc);
    float *Cout = (float *) malloc(sizeof(float)*M*ldc);

    //float mat[3];

    printf("[DEBUG] Reading matrices from the file\n");
    __read_matrices_from_file(A, B, Cin, Cout, M, K, N, lda, ldb, ldc);

    use_fx_conv = true;

    for(int i = 8; i < 20; i++) {
        scale = i;
        printf("[DEBUG] Computing snr for scale = %d\n", scale);
        compute_snr(A, B, Cin, Cout, M, K, N, lda, ldb, ldc, scale);
    }

    return;
}
