#include <stdio.h>

#define stack_length 15
int CMP_FLAG;
int eax, ebx, ecx, edx, esp = 0, ebp = 0;
int stack[stack_length] = { 0 };

#define ADD(x,y) y = x + y
#define SUB(x,y) y = y - x
#define MOV(x,y) y = x
#define INC(x)   x++
#define CMP(x,y)        \
    if(x < y)    CMP_FLAG = -1;\
    if(x > y)    CMP_FLAG = 1;\
    if (x == y)  CMP_FLAG = 0;   
#define JNE(L) if (CMP_FLAG != 0) goto L;
#define PRINT(x) printf("%d\n", x)
#define PUSH(x)\
for (int i = stack_length-1; i > 0; i--)\
{\
    stack[i] = stack[i - 1];\
}\
    stack[0] = x;\
    esp++;

#define POP(x)\
for (int i = 0; i < stack_length - 1; i++)\
{\
    x = stack[0];\
    stack[i] = stack[i + 1];\
    esp--;\
}   


int main()
{
    MOV(2, eax);
    ADD(2, eax);
    SUB(5, eax);
    INC(eax);
    PRINT(eax);
A:
    PUSH(eax);
    INC(eax);
    CMP(eax, 5);
    JNE(A);
    PRINT(eax);
    MOV(0, eax);
B:
    INC(eax);
    POP(ebx);
    PRINT(ebx);
    CMP(eax, 5);
    JNE(B);
}
