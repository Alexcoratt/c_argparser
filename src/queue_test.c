#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

int counter = 0;

char *allocString(const char *value) {
    if (!value)
        return NULL;
    
    size_t len = strlen(value);
    return memcpy(calloc(len + 1, sizeof(char)), value, len);
}

void printString(char *value) {
    printf("arg[%d] = %s\n", counter++, value);
}

int main(int argc, char **argv) {
    struct Queue q;
    initQueue(&q, (alloc_func *)&allocString, NULL);

    for (int i = 0; i < argc; ++i)
        pushQueue(&q, argv[i]);

    traverseQueue(&q, (queue_traverse_func *)&printString);
    destructQueue(&q);

    return 0;
}