#include <stdio.h>
int main() {
int x[5]={1,2,3,4,5};
  printf("%p\n", x);
  printf("%p\n", x+1);
  printf("%p\n", &x);
  printf("%p\n", &x+1);
  return 0;
}
