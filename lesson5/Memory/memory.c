#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>


static int8_t bss[5000];                     
static int8_t data[8000] = {1};           
static const int8_t rodata[10] = {"rodata"}; 
void maps();
void pmap();
void size_short();
void size_long();

int main(void)
{
    int param = 3;
    printf("************************************ \n");
    printf("code is at   %p \n", (void *)main);
    printf("rodata       %p \n", &rodata);
    printf("data         %p \n", &data);
    printf("bss at       %p \n", &bss);
    printf("heap is at   %p \n", malloc(8));
    printf("stack is at  %p \n", (void *)&param); 
    printf("************************************ \n");
    printf("bss at       %"PRIu8"\n", bss[0]);
    //maps();
    pmap();
    size_short();
    size_long();
    
    
    exit(EXIT_SUCCESS);
}

void maps()
{
	char cmd[64];
	sprintf(cmd, "cat /proc/%d/maps", getpid());
	system(cmd);
	printf("************************************ \n");
}

void pmap()
{
	char cmd[64];
	sprintf(cmd, "pmap %d ", getpid());
	system(cmd);
	printf("************************************ \n");
}

void size_short()
{
	system("size memory");
	printf("************************************ \n");
}

void size_long()
{
	system("size -A memory");
	printf("************************************ \n");
}
//gcc memory.c -o memory -m32 -nostartfiles
