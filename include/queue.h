#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "common.h"

struct SingleList {
    void *value;
    struct SingleList *next;
};

struct Queue {
    struct SingleList *first;   // first to go out
    struct SingleList *last;    // last went in

    size_t typeSize;

    alloc_func *alloc;
    delete_func *delete;
};

void initQueue(struct Queue *, size_t typeSize, alloc_func *alloc, delete_func *delete);
void destructQueue(struct Queue *);

void pushQueue(struct Queue *, const void *value);
void *popQueue(struct Queue *);

size_t sizeQueue(const struct Queue *);
bool isEmptyQueue(const struct Queue *);

#endif