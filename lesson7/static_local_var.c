#include <stdio.h>

int summ(int a)
{
    static int b = 5;
    b++;
    return a + b;
}

int main(void)
{
    int x = summ(5);
    printf("%d\n", x);
    x = summ(5);
    printf("%d\n", x);
    return 0;
}

