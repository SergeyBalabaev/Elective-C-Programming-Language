#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

#define N 16

double fRand(double, double);

__global__
void summ_V_GPU(double* a, double* b, double* c)
{
	int index = threadIdx.x;
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

	summ_V_GPU << <1, N >> > (dev_a, dev_b, dev_c);

	cudaMemcpy(c_1, dev_c, N * sizeof(double), cudaMemcpyDeviceToHost);


	summ_V_CPU(a, b, c);
	print_vector(a);
	print_vector(b);
	print_vector(c);
	print_vector(c_1);

	check_vectors(c, c_1);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	free(a);
	free(b);
	free(c);
	return 0;
}


double fRand(double fMin, double fMax)
{
double f = (double)rand() / RAND_MAX;
return fMin + f * (fMax - fMin);
}
