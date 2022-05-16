#include <stdio.h>

__attribute__((always_inline))
inline int summ(int a, int b)
{
    return a + b;
}

int main(void)
{
    int x = summ(5, 5);
    return 0;
}
