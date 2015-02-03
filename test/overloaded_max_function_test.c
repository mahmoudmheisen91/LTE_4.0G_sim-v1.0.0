#include <stdio.h>

#define max(a1,b1) if (sizeof(a1) / b1 == sizeof(int)) {\
    max_int(a1, b1); printf("if: %d\n", sizeof(a1) / b1 == sizeof(int));}\
    else {\
    max_double(a1, b1); printf("else: %d\n", sizeof(a1) / b1 == sizeof(int)); }


int max_int(int *data, int length) {
    int i;
    int result = -999999;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }
    return result;
}

double max_double(double *data, int length) {
    int i;
    double result = -999999.99;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }
    return result;
}

void main(void) {
    int a[3] = {-1, 0, 12};
    double b[4] = {5.0, -55.0, 26, 1};

    printf("max_int: %d\n", max_int(a, 3));
    printf("max_double: %0.2f\n", max_double(b, 4));

    max(a, 3);
    //printf("max: %0.2f\n", max(b, 4));

    //printf("size(a): %d\n", sizeof(b)/4);
    //printf("size(a): %d\n", sizeof(double));
}
