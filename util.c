#include "9cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void error(char *msg, char *input) {
    fprintf(stderr, "%s: %s\n", msg, input);
    exit(1);
}