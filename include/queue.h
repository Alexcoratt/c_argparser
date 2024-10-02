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

    alloc_func *alloc;
    delete_func *delete;
};

void initQueue(struct Queue *, alloc_func *, delete_func *);
void destructQueue(struct Queue *);

void pushQueue(struct Queue *, const void *value);
void *popQueue(struct Queue *);

size_t sizeQueue(const struct Queue *);
bool isEmptyQueue(const struct Queue *);

// auxillary functions
typedef void queue_traverse_func(void *);
void traverseQueue(const struct Queue *, queue_traverse_func *);

#endif