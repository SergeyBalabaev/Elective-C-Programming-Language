#include <stdio.h>

//#pragma pack(push, 1)
typedef struct S_1
{
        char ch;
        int value;
} S_1;
//#pragma pack(pop)

typedef struct S_2
{
        char ch;
        short sh_val;
        int value;
} S_2;


int main()
{
  S_1 s1;
  S_2 s2;
  printf("%ld\n", sizeof(s1));
  printf("%ld\n", sizeof(s2));
  return 0;
}
