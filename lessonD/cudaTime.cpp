#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

#define N 1024 * 1024 * 128
#define N_threads 1024

double fRand(double, double);

__global__
void summ_V_GPU(double* a, double* b, double* c)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	c[index] = a[index] + b[index];
}

void summ_V_CPU(double* a, double* b, double* c)
{
	for (size_t i = 0; i < N; i++)
	{
		c[i] = a[i] + b[i];
	}
}

void init_vectors(double* a, double* b)
{
	for (size_t i = 0; i < N; i++)
	{
		a[i] = fRand(0, 100);
		b[i] = fRand(0, 100);
	}
}

void print_vector(double* a)
{
	for (size_t i = 0; i < N; i++)
	{
		printf("v[%d] = %lf\n", i, a[i]);
	}
	printf("\n");
}

bool check_vectors(double* a, double* b)
{
	for (size_t i = 0; i < N; i++)
	{
		if (a[i] != b[i])
		{
			printf("Error!\n");
			return 1;
		}
	}
	printf("No errors :)\n");
	return 0;
}

int main()
{
	double* a = (double*)malloc(N * sizeof(double));
	double* b = (double*)malloc(N * sizeof(double));
	double* c = (double*)malloc(N * sizeof(double));
	double* c_1 = (double*)malloc(N * sizeof(double));
	init_vectors(a, b);

	double* dev_a, * dev_b, * dev_c;
	cudaMalloc((void**)&dev_a, N * sizeof(double));
	cudaMalloc((void**)&dev_b, N * sizeof(double));
	cudaMalloc((void**)&dev_c, N * sizeof(double));

	cudaMemcpy(dev_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start);
	summ_V_GPU << <N / N_threads, N_threads >> > (dev_a, dev_b, dev_c);
	cudaEventRecord(stop);
	cudaMemcpy(c_1, dev_c, N * sizeof(double), cudaMemcpyDeviceToHost);

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	summ_V_CPU(a, b, c);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = (t2 - t1);

	cudaEventSynchronize(stop);
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	printf("CPU time = %lf\n", duration);
	printf("GPU time = %lf\n", milliseconds / 1000);
	check_vectors(c, c_1);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	free(a);
	free(b);
	free(c);
	return 0;
}
