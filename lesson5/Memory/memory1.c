#include <stdio.h> 
#include <stdlib.h>

static int bss[1024]; 
static int data[1024] = {1024}; 
static const char rodata[8192] = {"rodata"}; 

int main(void) 
{ 
  int stack; 
  int *heap = (int*)malloc(1024*sizeof(int)); 
  free(heap); 
  return 0; 
} 
