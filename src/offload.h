#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAP_SIZE 0x10000ul
#define MAP_MASK (MAP_SIZE - 1)

int init_memory();
void delete_momory();
void offload_a_b(int a, int b);

void offload_ints(int arr[], unsigned int address, int size);
void offload_A_chunk(int arr[], int size);
void offload_B_chunk(int arr[], int size);

void offload_floats(float a, unsigned int address, int size);

int get_c();
float get_c_float();
int get_c_int();

void copy_convert_A_into_vec1(float A[], int* vec1, int size, int k_start, int scale, int SCALE_NUM, int ALPHA_con);
void copy_convert_B_into_vec2(float B[], int* vec2, int size, int k_start, int scale, int SCALE_NUM, int ldb, int j);

void set_array_boundaries_accelerator(int M, 
                                     int N, 
                                     int K, 
                                     int lda, 
                                     int ldb, 
                                     int ldc);
