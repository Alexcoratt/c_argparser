#include <stdlib.h>
#include <string.h>

#include "queue.h"

void initQueue(struct Queue *q, size_t typeSize, alloc_func *alloc, delete_func *delete) {
    q->last = q->first = NULL;
    q->typeSize = typeSize;

    q->alloc = alloc ? alloc : defaultAlloc;
    q->delete = delete ? delete : defaultDelete;
}

void destructQueue(struct Queue *q) {
    while (q->first) {
        q->delete(q->first->value);
        struct SingleList *next = q->first->next;
        free(q->first);
        q->first = next;
    }
}

void pushQueue(struct Queue *q, const void *value) {
    struct SingleList *newItem = T_MALLOC(struct SingleList);
    newItem->value = q->alloc(q->typeSize);
    memcpy(newItem->value, value, q->typeSize);
    newItem->next = NULL;

    if (!q->last)
        q->first = q->last = newItem;
    else
        q->last = q->last->next = newItem;
}

void *popQueue(struct Queue *q) {
    void *res = q->first->value;
    struct SingleList *second = q->first->next;
    free(q->first);
    q->first = second;
    if (!second)
        q->last = NULL;
    return res;
}

size_t sizeQueue(const struct Queue *q) {
    size_t size = 0;
    for (const struct SingleList *slptr = q->first; slptr; slptr = slptr->next, ++size);
    return size;
}

bool isEmptyQueue(const struct Queue *q) {
    return q->last == NULL;
}