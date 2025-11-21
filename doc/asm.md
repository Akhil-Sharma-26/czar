### Understanding ASM
```asm
global _start
_start: # This is the start of the asm program
    ret # Just returning 
```

I am using `nasm` to convert `asm` into a `object` file by:
`nasm -felf64 a.asm`

and then linking it with `ld`:
`ld a.o -o abc`

This will give us an exec `abc`. But running it will give us a `seg fault`. BECAUSE we are so low level, we have to tell the Kernel that we are done, doing just `ret` will not work


- Linux syscalls `x86_64` -> [Link](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)


- So we have to do a `exit()` syscall to successfully exit.

```wasm
mov rax, 60 # this is exit sys call opcode
mov rdi, 69 # The arg to the exit sys call to the rdi register
syscall
  ```

- `rdi` is 8 bit register. So can't go above 255