.intel_syntax noprefix
.global _main

_main:
    push 2
    push 3

    pop rdi
    pop rax
    imul rax, rdi
    push rax

    push 4
    push 5

    pop rdi
    pop rax
    imul rax, rdi
    push rax

    pop rdi
    pop rax
    add rax, rdi

    ret
