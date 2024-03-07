#include <stdio.h>
#include "lib.h"
#define X 10
const int a = 10;
int main()
{
	int res_sum, res_mult;
	summ(X, a, &res_sum);
	mult(2, 2, &res_mult);
	if(res_sum < res_mult) // comment
		printf("Sum = %d\n", res_sum);
	else
		printf("Mult = %d\n", res_mult);
	return 0;
}
