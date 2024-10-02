#include <stdio.h>
#include "queue.h"

int main(int argc, char **argv) {
    struct Queue q;
    initQueue(&q, sizeof(char *), NULL, NULL);

    for (int i = 0; i < argc; ++i)
        pushQueue(&q, argv + i);

    for (int i = 0; i < argc; ++i) {
        void *value = popQueue(&q);
        printf("arg[%d] = %s\n", i, *(char **)value);
        q.delete(value);
    }

    return 0;
}