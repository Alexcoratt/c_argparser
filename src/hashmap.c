#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "common.h"

// string pair methods definitions
struct StringPair *initStringPairPtr(char *key, void *value) {
    struct StringPair *res = T_MALLOC(struct StringPair);
    res->key = key;
    res->value = value;
    return res;
}

void freeStringPair(struct StringPair *sp) {
    free(sp);
}

// TODO: Improve the default hash function
size_t defaultStrHash(const char *value) {
    size_t res = 0;
    for (size_t i = 0; *value; ++i, ++value)
        res += (i + 1) * (*value);
    return res;
}

// definitions of hashmap methods
void hm_init(struct Hashmap *hmap, size_t capacity, str_hash_func hash, alloc_func alloc, del_func del) {
    hmap->capacity = capacity;
    hmap->size = 0;
    hmap->cells = T_CALLOC(sstack, capacity);

    hmap->hash = hash ? hash : defaultStrHash;

    hmap->alloc = alloc;
    hmap->del = del ? del : defaultDel;
}

void hm_free(struct Hashmap *hmap) {
    for (size_t i = 0; i < hmap->capacity; ++i) {
        sstack *cell = hmap->cells + i;
        while (*cell) {
            struct StringPair *sp = (struct StringPair *)sstack_pop(cell);
            hmap->del(sp->value);
            freeString(sp->key);
            freeStringPair(sp);
        }
    }

    free(hmap->cells);
}

bool keyEqual(const char *key, const struct StringPair *sp) {
    return eqStrings(key, sp->key);
}

void hm_set(struct Hashmap *hmap, const char *key, const void *value) {
    size_t h = hmap->hash(key);
    size_t index = h % hmap->capacity;

    sstack found = *sstack_find(hmap->cells + index, key, (eq_func)keyEqual);
    if (found) {
        struct StringPair *sp = (struct StringPair *)found->value;
        hmap->del(sp->value);
        sp->value = hmap->alloc(value);
        return;
    }

    if (hmap->size + 1 > hmap->capacity) {
        hm_resize(hmap, hmap->capacity * 2);
        index = h % hmap->capacity;
    }

    sstack_push(hmap->cells + index, initStringPairPtr(allocString(key), hmap->alloc(value)));
    ++(hmap->size);
}

void hm_erase(struct Hashmap *hmap, const char *key) {
    sstack *found = sstack_find(hmap->cells + (hmap->hash(key) % hmap->capacity), key, (eq_func)keyEqual);
    if (*found) {
        struct StringPair *sp = (struct StringPair *)sstack_pop(found);
        hmap->del(sp->value);
        freeString(sp->key);
        freeStringPair(sp);
        --(hmap->size);
    }
}

void **hm_get(const struct Hashmap *hmap, const char *key) {
    sstack found = *sstack_find(hmap->cells + hmap->hash(key) % hmap->capacity, key, (eq_func)keyEqual);
    if (found)
        return &((struct StringPair *)found->value)->value;
    return NULL;
}

void hm_resize(struct Hashmap *hmap, size_t newCapacity) {
    sstack *newCells = T_CALLOC(sstack, newCapacity);

    for (size_t i = 0; i < hmap->capacity; ++i) {
        sstack *cell = hmap->cells + i;
        while (*cell) {
            struct StringPair *sp = (struct StringPair *)sstack_pop(cell);
            size_t index = hmap->hash(sp->key) % newCapacity;
            sstack_push(newCells + index, sp);
        }
    }

    free(hmap->cells);
    hmap->cells = newCells;
}

static hm_traverse_func trav_func = NULL;
static void pair_stack_func(struct StringPair *sp) {
    trav_func(sp->key, sp->value);
}

void hm_traverse(const struct Hashmap *hmap, hm_traverse_func func) {
    trav_func = func;
    for (size_t i = 0; i < hmap->capacity; ++i)
        sstack_traverse(hmap->cells[i], (sstack_traverse_func)pair_stack_func);
}