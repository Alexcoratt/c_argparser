#include <stdio.h>
#include "common.h"
#include "stack.h"

int counter = 0;

void printArg(char *arg) {
    printf("argv[%d] = %s\n", counter--, arg);
}

int main(int argc, char **argv) {
    struct Stack st;
    stack_init(&st, (alloc_func)allocString, NULL);

    for (counter = 0; counter < argc; ++counter)
        stack_push(&st, argv[counter]);

    --counter;
    stack_traverse(&st, (sstack_traverse_func)printArg);

    stack_free(&st);

    return 0;
}