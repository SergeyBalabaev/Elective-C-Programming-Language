#include <stdio.h>

int main()
{
	int sum = 0, x = 1, y = 2;
	asm("add %1, %0" 
		: "=r" (sum) 
		: "r" (x), "0" (y)); // sum = x + y;
	printf("sum = %d, x = %d, y = %d \n", sum, x, y); // sum = 3, x = 1, y = 2
	return 0;
}
