#include <stdio.h>
int main() {
    int x[5] = { 1,2,3,4,5 };
    int(*y)[5] = &x;
    int(*z) = &x;
    printf("x: \t%p\n", x);
    printf("x+1: \t%p\n", x + 1);
    printf("*y: \t%p\n", *y);
    printf("*y+1: \t%p\n", *y + 1);
    printf("*z: \t%p\n", *z);
    printf("*z+1: \t%p\n", *z + 1);
    return 0;
}
