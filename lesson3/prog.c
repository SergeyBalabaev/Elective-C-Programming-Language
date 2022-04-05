#include <stdio.h>
#define X 10

void summ(int x, int y, int* sum) //comment
{
	*sum = x + y;
}

void mult(int x, int y, int* mult)
{
	*mult = x * y;
}

int main()
{
int res_sum, res_mult;
summ(10, X, &res_sum);
mult(2, 2, &res_mult);
if(res_sum < res_mult)
	printf("Sum = %d\n", res_sum);
else
	printf("Mult = %d\n", res_mult);
return 0;
}
