#ifndef QUEUE_H
#define QUEUE_H

#include "single_list.h"
#include "common.h"

struct Queue {
    struct SingleList *first;   // first to go out
    struct SingleList *last;    // last went in

    alloc_func *alloc;
    del_func *del;
};

void initQueue(struct Queue *, alloc_func *, del_func *);
void destructQueue(struct Queue *);

void pushQueue(struct Queue *, const void *value);
void *popQueue(struct Queue *);

size_t sizeQueue(const struct Queue *);
bool isEmptyQueue(const struct Queue *);

// auxillary functions
void traverseQueue(const struct Queue *, single_list_traverse_func *);

#endif