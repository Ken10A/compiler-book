#include "9cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_alnum(char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           (c == '_');
}


Node *assign() {
    Node *node = add();
    while (consume('='))
        node = new_node('=', node, assign());
    return node;
}

Node *stmt() {
    Node *node;

    if (consume(TK_RETURN)) {
        node = malloc(sizeof(Node));
        node->ty = ND_RETURN;
        node->lhs = assign();
    } else {
        node = assign();
    }

    if (!consume(';'))
        error("Found not ';' token %s", tokens[pos].input);
    return node;
}

void program() {
    int i = 0;
    while (tokens[pos].ty != TK_EOF)
        code[i++] = stmt();
    code[i] = NULL;
}

void tokenize(char *p) {
    int i = 0;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if ('a' <= *p && *p <= 'z') {
            tokens[i].ty = TK_IDENT;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }

        if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')') {
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }

        if (isdigit(*p)) {
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p, &p, 10);
            i++;
            continue;
        }

        if (strncmp(p, "return", 6) == 0 && !is_alnum(p[6])) {
            tokens[i].ty = TK_RETURN;
            tokens[i].input = p;
            i++;
            p += 6;
            continue;
        }

        fprintf(stderr, "can't tokenize %s\n", p);
        exit(1);
    }

    tokens[i].ty = TK_EOF;
    tokens[i].input = p;
}