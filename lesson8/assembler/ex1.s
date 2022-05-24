 .global _start
        .text
_start:
        # write(1, message, 12)
        mov     $1, %rax                # системный вызов 1
        mov     $1, %rdi                # связываем с файловым дескриптором 1
        mov     $message, %rsi          # передаем адрес строки
        mov     $12, %rdx               # размер строки
        syscall                         # системный вызов

        # exit(0)
        mov     $60, %rax               # системный вызов 1
        mov     $0, %rdi                # передаем 0 в качетсе аргумента
        syscall                         # системный вызов
        .data
message:
        .ascii  "Hello, MIET\n"
