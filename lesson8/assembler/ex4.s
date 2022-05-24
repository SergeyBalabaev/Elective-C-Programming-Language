.data
printf_format:
        .string "%d\n"
 
.text
.global main
main:
        movl  $0, %eax          
        movl  $10, %ecx        
sum:
        addl  %ecx, %eax        
        loop  sum
 
        /* %eax = 55, %ecx = 0 */
 
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl  $0, %eax
        ret
