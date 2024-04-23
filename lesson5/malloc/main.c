#include "malloc_lib.h" 

void test1();
void test2();

int main()
{
	test1();
	test2();
	return 0;
}

void test1()
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
}

void test2()
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
}
