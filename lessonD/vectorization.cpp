#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <iostream>
using namespace std;


int main(void)
{
    int N = 20 * (1 << 25);
    float* x, * y, * z;
    x = (float*)malloc(N * sizeof(float));
    y = (float*)malloc(N * sizeof(float));
    z = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = (chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
    printf("Time vec: %f\n", (double)duration / 1000);
    free(x);
    free(y);
    free(z);
    return 0;
}
