#include <stdio.h>

int max(int *data, int length) {
    int i;
    int result = -999999;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }
    return result;
}

double max(double *data, int length) {
    int i;
    double result = -999999.99;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }
    return result;
}

int main(void) {
    int a[3] = {-1, 0, 12};
    double b[4] = {5.0, -55.0, 26, 1};

    printf("max_int: %d\n", max(a, 3));
    printf("max_double: %0.2f\n", max(b, 4));

    return 1;
}
