#include <stdio.h>

int main()
{
	int x[3] = {1,2,3};
	printf("%d\n",x[1]);
	printf("%d\n",*(x+1));
	printf("%d\n",1[x]);
	printf("%d\n",*(&x[1]));
	return 0;
}
