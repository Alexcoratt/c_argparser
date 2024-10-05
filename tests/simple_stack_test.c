#include <stdio.h>
#include "simple_stack.h"

int counter = 0;

void printArg(char *arg) {
    printf("argv[%d] = %s\n", counter--, arg);
}

int main(int argc, char **argv) {
    sstack ss = EMPTY_SSTACK;
    for (int i = 0; i < argc; ++i)
        sstack_push(&ss, argv[i]);

    printf("stack size: %lu\n", sstack_size(ss));

    counter = argc - 1;
    sstack_traverse(ss, (sstack_traverse_func)printArg);

    while (ss != EMPTY_SSTACK)
        sstack_pop(&ss);

    return 0;
}