#include <stdio.h>
#include <stdlib.h>

int main() {
int N_mas = 10;
double** A = (double**)malloc(N_mas * sizeof(double*));
for (int i = 0; i < N_mas; i++) {
	A[i] = (double*)malloc(N_mas * sizeof(double));
}

free(A);
return 0;
}
