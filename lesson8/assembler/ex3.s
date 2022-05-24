        .global _start
        .text
_start:

        movq     $0, %rbx
N_EQ:
        mov     $1, %rax                
        mov     $1, %rdi               
        mov     $mes, %rsi          
        mov     $9, %rdx               
        syscall  

        add     $1, %rbx
        cmp     $5, %rbx              
        jne N_EQ

        mov     $1, %rax                
        mov     $1, %rdi               
        mov     $mes_2, %rsi          
        mov     $9, %rdx               
        syscall  

        mov     $60, %rax               
        mov     $0, %rdi                
        syscall                         
        
        .data
mes:
    .ascii "no equal\n"
mes_2:
    .ascii "equal\n"
