#include <stdio.h>
#include "queue.h"

int counter = 0;

void printArg(char *value) {
    printf("arg[%d] = %s\n", counter++, value);
}

int main(int argc, char **argv) {
    struct Queue q;
    queue_init(&q, (alloc_func)allocString, NULL);

    for (int i = 0; i < argc; ++i)
        queue_push(&q, argv[i]);

    queue_traverse(&q, (sstack_traverse_func)printArg);
    queue_free(&q);

    return 0;
}