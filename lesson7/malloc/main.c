#include <stdio.h>
#include "malloc_lib.h" 

int main()
{
	int N_mas = 10;
	double** A = (double**)malloc(N_mas * sizeof(double*));
	for (int i = 0; i < N_mas; i++) {
		A[i] = (double*)malloc(N_mas * sizeof(double));
	}
	for (int i = 0; i < N_mas; i++) {
		free(A[i]);
	}
	free(A);
	return 0;
}


/*
#include <stdio.h> 
#include "malloc_lib.h" 

const int N = 50;

int main()
{
	int* a = (int*)malloc(10);
	int* b = (int*)malloc(15);
	int* c = (int*)malloc(10);
	free(b);
	int* d = (int*)malloc(5);
	int* e = (int*)malloc(5);
	free(a);
	free(c);
	free(d);
	free(e);
	return 0;
}
*/