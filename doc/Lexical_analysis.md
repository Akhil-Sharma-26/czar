So It all starts with converting
`return 42;` from my `first.czar` into
```wasm
global _start
_start:
    mov rax, 60 
    mov rdi, 69 
    syscall
```

Lexical tokenization(analysis) is conversion of a text into (semantically or syntactically) meaningful lexical tokens belonging to categories defined by a "lexer" program.


