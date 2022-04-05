#include <stdio.h>
#define X
int main()
{
    int a = 0;
#ifdef X 
    a = 10;
#endif 

#ifndef X 
    a = 20;
#endif 

    printf("%d\n", a);
    return 0;
}
