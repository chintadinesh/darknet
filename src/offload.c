#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define MAP_SIZE 0x10000ul
#define MAP_MASK (MAP_SIZE - 1)

volatile unsigned int *base, *address, * address_a, *address_b, *address_c;

//volatile float *address_a_float, *address_b_float, *address_c_float;

volatile unsigned int *address_a_int, *address_b_int; 
volatile unsigned int *address_c_int;

volatile int  *accel_addr_M, *accel_addr_N, *accel_addr_K, 
                        *accel_addr_lda, *accel_addr_ldb, *accel_addr_ldc; 

volatile unsigned int *address_int;

long addr1, addr2, addr3, addr4, addr0, offset, value;
long addr5, addr6, addr7, addr8, addr9;
long addr_M, addr_N, addr_K, addr_lda, addr_ldb, addr_ldc; 

long val, result;
int fd;

int init_memory() {

#ifdef MYDEBUG
    printf("Initilizing memory\n");
#endif
    /*
    * In our model, we use three addresses,
    * 1. for writing a
    * 2. for writing b
    * 3. for getting output
    */

    addr0 = 0xa0000000ul;  // c, the result
    addr1 = 0xa0000004ul;  // a, the first value
    addr2 = 0xa0000008ul;  // b, the second value
    addr3 = 0xa000000Cul;  // DEBUG_IRQ

    /*
     * Let us exploit the fact that the filter sizes = 3*3 for the best part
     * of darknet.
     * Hence, we send 9 numbers at once.
     * size = 9 * 4 bytes = 100100 = 0x24
     */

    /*
    addr4 = 0xa0000020ul;  // c, the result in float type
    addr5 = 0xa0000024ul;  // a array of 256 bytes
    addr6 = 0xa0000048ul;  // b array of 
    */

    /*
     * Let us exploit the fact that the filter sizes = 3*3 for the best part
     * of darknet.
     * Hence, we send 9 numbers at once.
     * size = 9 * 4 bytes = 100100 = 0x24
     */

    addr7 = 0xa0000020ul;  // c, the result in int type

    addr8 = 0xa0002000ul;  // a array of 256 bytes
    addr9 = 0xa0003000ul;  // b array of 

    addr_M        = 0xa0000100ul;  
    addr_N        = 0xa0000104ul;  
    addr_K        = 0xa0000108ul;  
    addr_lda      = 0xa000010cul;
    addr_ldb      = 0xa0000110ul;
    addr_ldc      = 0xa0000114ul;

    //Open memory as a file
    fd = open("/dev/mem", O_RDWR|O_SYNC);
    if(!fd) {
        printf("Unable to open /dev/mem.  Ensure it exists (major=1, minor=1)\n");
        return -1;
    }	

    //Map the physical base address to local pointer (in virtual address space)
    base = (unsigned int *)mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr0 & ~MAP_MASK);	
    if((base == MAP_FAILED))
    {
        printf("[FATAL] mapping failed\n");
        exit(1);
    }


    address_a = base + ((addr1 & MAP_MASK)>>2);
    address_b = base + ((addr2 & MAP_MASK)>>2);
    address_c = base + ((addr0 & MAP_MASK)>>2);
    address_int = base + ((addr3 & MAP_MASK)>>2);

    /*
    address_a_float = base + ((addr5 & MAP_MASK)>>2);
    address_b_float = base + ((addr6 & MAP_MASK)>>2);
    address_c_float = base + ((addr4 & MAP_MASK)>>2);
    */

    address_a_int = base + ((addr8 & MAP_MASK)>>2);
    address_b_int = base + ((addr9 & MAP_MASK)>>2);
    address_c_int = base + ((addr7 & MAP_MASK)>>2);


    accel_addr_M = base + ((addr_M & MAP_MASK)>>2);
    accel_addr_N = base + ((addr_N & MAP_MASK)>>2);
    accel_addr_K = base + ((addr_K & MAP_MASK)>>2);
    accel_addr_lda = base + ((addr_lda & MAP_MASK)>>2);
    accel_addr_ldb = base + ((addr_ldb & MAP_MASK)>>2);
    accel_addr_ldc = base + ((addr_ldc & MAP_MASK)>>2);

#ifdef MYDEBUG
    printf("Successfully initilized momory.\n");
#endif

    return 0;
}

void delete_momory() {
    munmap((void*)base, MAP_SIZE);
    close(fd);
    return;
}

void offload_a_b(int a, int b) {
    *address_a = a; *address_b = b; 

    // raise the interrupt saying that the inputs are ready
    *address_int = 1;
}

/*
void offload_floats(float arr[], unsigned int address, int size) {

    memcpy(address, arr, size * sizeof(float));

    return;
}
*/


void offload_A_chunk(int arr[], int size) {
    #pragma message("Inside offloading loop")


#ifdef MYDEBUG
    printf("Reading current interrupt values.\n");

//    if(address_int == NULL) 
//        printf("address_int is NULL\n");
//    else
//        printf("Reading from address %d\n", address_int);
//
//    int curr = *address_int;
//
//    printf("Current interrupt values is %d\n", curr);
//
//    printf("Setting the interrupt bit to 1.\n");
//    fflush(stdout);
#endif

//    *address_int = 1;

#ifdef MYDEBUG
    printf("memcpy the array.\n");
    //fflush(stdout);
#endif
    for(int i = 0; i < size; i++) *(address_a_int +i) = arr[i];
    //memcpy(address_a_int,  arr, size * sizeof(int));

    // wait until the vaule is written 
#ifdef MYDEBUG
    printf("Waiting until the interrupt is cleared.\n");
 //   fflush(stdout);
#endif

//    while(*address_int == 1)
//        ;

#ifdef MYDEBUG
    printf("Completed copying of A\n");
//    fflush(stdout);
#endif

    return;
}

void offload_B_chunk(int arr[], int size) {
    #pragma message("Inside offloading loop")
//    *address_int = 1;
    for(int i = 0; i < size; i++) *(address_b_int +i) = arr[i];
    //memcpy(address_b_int,  arr, size * sizeof(int));
    // wait until the vaule is written
//    while(*address_int == 1)
//        ;

    return;
}


/*
float get_c_float() {
    static float c = -1;

    c = -1;

#ifdef MYDEBUG
    printf("Waiting for the interruput value to be changed\n");
#endif

    // wait until the vaule is written and then read
    while(*address_int == 1)
        ;

    c = *address_c_float;

#ifdef MYDEBUG
    printf("Received the value %d\n", c);
#endif

    return c;
}
*/

int get_c() {
    static int c = -1;

    c = -1;

#ifdef MYDEBUG
    printf("Waiting for the interruput value to be changed\n");
#endif

    *address_int = 1;
    c = *address_c;

    // wait until the vaule is written and then read
    while(*address_int == 1)
        ;

    c = *address_c;


#ifdef MYDEBUG
    printf("Received the value %d\n", c);
#endif

    return c;
}

int get_c_int() {
    static int c = -1;

    c = -1;

#ifdef MYDEBUG
    printf("Waiting for the interrupt value to be changed\n");
#endif

    *address_c_int = 1;
    c = *address_c_int;

    // wait until the vaule is written and then read
    while(*address_int == 1)
        ;

    c = *address_c_int;

#ifdef MYDEBUG
    printf("Received the value %d\n", c);
#endif

    return c;
}

/* 
 * While offloading, create the two vectors.
 * It also converts the floats to ints
 * Assumption: M = 1 in the passing function. This would obviate i*lda
 * multiplications
 */
void copy_convert_A_into_vec1(float A[], 
                                int* vec1, 
                                int size, 
                                int k_start, 
                                int scale, 
                                int SCALE_NUM, 
                                int ALPHA_con){

    #pragma message("Inside offloading loop")
    for(int k=k_start; k < (k_start + size); k++) {
        *(vec1 + (k - k_start)) = (ALPHA_con * (int)(A[k] * SCALE_NUM))
                    >> scale;
    }

    return;
}

void copy_convert_B_into_vec2(float B[], 
                              int* vec2, 
                              int size, 
                              int k_start, 
                              int scale, 
                              int SCALE_NUM, 
                              int ldb, 
                              int j){

    #pragma message("Inside offloading loop")
    //printf("[DEBUG] B = ");
    for(int k=k_start; k < (k_start + size); k++) {
        int b = B[k * ldb + j];
        *(vec2 + (k-k_start)) = (int)( b * SCALE_NUM);
     //   printf("%d, %d ", b, *(vec2 + (k-k_start)));
    }
    //printf("\n");

    return;
}

void set_array_boundaries_accelerator(int M, 
                                     int N, 
                                     int K, 
                                     int lda, 
                                     int ldb, 
                                     int ldc) {
    *accel_addr_M = M;
    *accel_addr_N = N;
    *accel_addr_K = K;
    *accel_addr_lda = lda;
    *accel_addr_ldb = ldb;
    *accel_addr_ldc = ldc;

    return;
}
