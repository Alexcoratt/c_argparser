#include <stdlib.h>
#include "simple_stack.h"
#include "common.h"

struct SingleList *initSingleListPtr(void *value, struct SingleList *next) {
    struct SingleList *res = T_MALLOC(struct SingleList);
    res->value = value;
    res->next = next;
    return res;
}

void freeSingleList(struct SingleList *sl) {
    free(sl);
}

void sstack_push(sstack *ss, void *value) {
    *ss = initSingleListPtr(value, *ss);
}

void *sstack_pop(sstack *ss) {
    if (!*ss)
        return NULL;
    
    void *res = (*ss)->value;
    sstack next = (*ss)->next;
    freeSingleList(*ss);
    *ss = next;
    return res;
}

size_t sstack_size(sstack ss) {
    size_t res = 0;
    for (; ss; ss = ss->next, ++res);
    return res;
}

// auxillary methods
void sstack_traverse(sstack ss, sstack_traverse_func func) {
    for (; ss; func(ss->value), ss = ss->next);
}

sstack *sstack_find(sstack *ss, const void *example, eq_func eq) {
    for (; *ss != EMPTY_SSTACK && !eq(example, (*ss)->value); ss = &(*ss)->next);
    return ss;
}