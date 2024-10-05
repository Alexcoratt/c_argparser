#include <stdio.h>
#include "common.h"
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

    sstack *found = sstack_find(&ss, "test", (eq_func)eqStrings);
    if (*found)
        printf("found: %s\n", (char *)sstack_pop(found));
    else
        puts("not found");

    while (ss != EMPTY_SSTACK)
        sstack_pop(&ss);

    return 0;
}