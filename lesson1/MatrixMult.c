#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

/*
Cache demonstration
./matr 1000
valgrind --tool=cachegrind ./matr 500
cg_annotate cachegrind.out.XXXXXX
*/
// Функция выделения памяти под 2-ный массив
double** malloc_array(long int N){
	double **matrix = (double **)malloc(N*sizeof(double *));	
	for(int i = 0; i < N; i++) {
	 	   matrix[i] = (double *)malloc(N*sizeof(double));
}	
return matrix;
}

// Функция освобождения памяти 
void free_array(double** matrix,long int n){
	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

// Функция инициализации матрицы случайными числами из [0,1]
void rand_init_matrix(double** matrix,long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = rand() / RAND_MAX;
}

// Функция обнуления матрицы
void zero_init_matrix(double** matrix, long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0.0 ;
}


void mult_ijk(double** A, double** B, double** C, long int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
}

void mult_jik(double** A, double** B, double** C, long int N)
{
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
}

void mult_ikj(double** A, double** B, double** C, long int N)
{
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				C[i][j] += A[i][k] * B[k][j];
}

void mult_jki(double** A, double** B, double** C, long int N)
{
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				C[i][j] += A[i][k] * B[k][j];
}


int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		fprintf(stderr, "where <n> is the dimension of the matrix\n");
		return 1;
    	}
	
	long int N = strtol(argv[1], NULL, 10);
	double** A, **B, **C;
	srand(time(NULL));
// Выделение памяти под матрицы A,B,C
	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);

// Инициализация матриц
	rand_init_matrix(A, N);
	rand_init_matrix(B, N);
	zero_init_matrix(C, N);
	double timer;
	struct timeval tstart, tend;
	
// Перемножение матриц с порядком циклов ijk
	gettimeofday(&tstart, NULL);
	mult_ijk(A,B,C,N);
	gettimeofday(&tend, NULL);
	timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
	printf("Time ijk loops is %g seconds\n", timer);
	
// Перемножение матриц с порядком циклов jik
	zero_init_matrix(C, N);
	gettimeofday(&tstart, NULL);
	mult_jik(A,B,C,N);
	gettimeofday(&tend, NULL);
	timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
	printf("Time jik loops is %g seconds\n", timer);

// Перемножение матриц с порядком циклов ikj
	zero_init_matrix(C, N);
	gettimeofday(&tstart, NULL);
	mult_ikj(A,B,C,N);
	gettimeofday(&tend, NULL);
	timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
	printf("Time ikj loops is %g seconds\n", timer);

// Перемножение матриц с порядком циклов jki
	zero_init_matrix(C, N);
	gettimeofday(&tstart, NULL);
	mult_jki(A,B,C,N);
	gettimeofday(&tend, NULL);
	timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
	printf("Time jki loops is %g seconds\n", timer);
	


	
// Освобождение памяти занимаемой матрицами A,B,C
	free_array(A, N);
	free_array(B, N);
	free_array(C, N);
	return 0;
}
