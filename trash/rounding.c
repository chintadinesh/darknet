#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float i = 234.5678;
    int a = 1;
    printf("Before rounding = %10.10f, After rounding = %d\n", i,
        (int)(i + a));

    return 0;
}
