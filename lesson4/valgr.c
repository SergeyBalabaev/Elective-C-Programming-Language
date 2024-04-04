#include <stdio.h>
#include <stdlib.h>

void input_array(double *x, int N)
{
    int arrMax = 100, arrMin = 0;
    for (int i = 0; i < N; i++)
        x[i] = arrMin + (arrMax - arrMin) * ((double) rand() / RAND_MAX);
}

void print_array(double* x, int N)
{
    for (int i = 0; i < N; i++)
        printf("%lf ",x[i]);
    printf("\n ");
}

void increace_array(double** x, int N, int N_new)
{
    double* temp;
    temp = (double*)realloc(*x, N_new*sizeof(double));
    if(temp==NULL){
        printf("Error\n");
        return;
    }
    *x = temp;
}

int main()
{
    int arr_len = 10;
    double* array_heap = (double*)malloc(arr_len * sizeof(double));
    input_array(array_heap, arr_len);

    print_array(array_heap, arr_len);
    increace_array(&array_heap, arr_len, arr_len + 20);
    print_array(array_heap, arr_len);
    free(array_heap);
    return 0;
}
