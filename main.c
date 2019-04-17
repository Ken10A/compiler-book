#include "9cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong number of argument\n");
        return 1;
    }

    if (strcmp(argv[1], "-test") == 0)
        runtest();
    else {
        tokenize(argv[1]);
        program();

        printf(".intel_syntax noprefix\n");
        printf(".global _main\n");
        printf("_main:\n");

        printf("    push rbp\n");
        printf("    mov rbp, rsp\n");
        printf("    sub rsp, 208\n");

        for (int i = 0; code[i]; i++) {
            gen(code[i]);
            printf("    pop rax\n");
        }

        printf("    mov rsp, rbp\n");
        printf("    pop rbp\n");
        printf("    ret\n");
        return 0;
    }
}
