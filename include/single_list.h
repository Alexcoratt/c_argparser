#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <stddef.h>
#include <stdbool.h>

struct SingleList {
    void *value;
    struct SingleList *next;
};

#define EMPTY_SINGLE_LIST NULL

void pushSingleList(struct SingleList **, void *value);
void *popSingleList(struct SingleList **);

size_t sizeSingleList(struct SingleList *);
bool isEmptySingleList(struct SingleList *);

// auxillary methods
typedef void single_list_traverse_func(void *);
void traverseSingleList(struct SingleList *, single_list_traverse_func *);

#endif