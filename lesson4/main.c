#include <stdio.h>
#include "lib.h"

int main()
{
  int res_sum, res_mult;
  summ(10, 10, &res_sum);
  mult(2, 2, &res_mult);
  if(res_sum < res_mult)
    printf("Sum = %d\n", res_sum);
  else
    printf("Mult = %d\n", res_mult);
  return 0;
}
