#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <iostream>
using namespace std;

typedef double my_float;

int main(void)
{
    int N = 20 * (1 << 24);
    my_float* x, * y, *z;
    x = (my_float*)malloc(N * sizeof(my_float));
    y = (my_float*)malloc(N * sizeof(my_float));
    z = (my_float*)malloc(N * sizeof(my_float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

    chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
    #pragma loop(no_vector)
    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }
    chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
    auto duration = (chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
    auto duration2 = (chrono::duration_cast<chrono::milliseconds>(t4 - t3).count());
    printf("Time : %f\n", (double)duration / 1000);
    printf("Time novec: %f\n", (double)duration2 / 1000);
    printf("Tnv/Tv: %f\n", (double)duration2 / (double)duration);
    free(x);
    free(y);
    free(z);
    return 0;
}
