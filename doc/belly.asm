global _start
_start:
    mov rax, 60 ; this is exit sys call opcode
    mov rdi, 69 ; The arg to the exit sys call to the rdi register
    syscall

