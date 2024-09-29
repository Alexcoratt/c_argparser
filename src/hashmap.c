#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// key value pair
struct KeyVal {
    size_t keySize;
    char *key;
    void *value;
};

// single linked list to store key value pairs
struct KVSinglist {
    struct KeyVal kv;
    struct KVSinglist *next;
};

#define EMPTY_STACK NULL

void pushKVStack(KVStack *kvs, struct KeyVal kv) {
    KVStack newItem = malloc(sizeof(struct KVSinglist));
    newItem->kv = kv;
    newItem->next = *kvs;
    *kvs = newItem;
}

struct KeyVal popKVStack(KVStack *kvs) {
    KVStack next = (*kvs)->next;
    struct KeyVal res = (*kvs)->kv;
    free(*kvs);
    *kvs = next;
    return res;
}

KVStack *findKVStack(KVStack *kvs, size_t keySize, const char *key) {
    KVStack *res = kvs;
    for (; *res && ((*res)->kv.keySize != keySize || strncmp((*res)->kv.key, key, keySize) != 0); res = &(*res)->next);
    return res;
}

// definitions of hashmap methods

size_t defaultHash(size_t, const char *);
void defaultDelete(void *);

void initHashmap(struct Hashmap *hmap, size_t capacity, hash_func hasher, delete_func deleter) {
    hmap->capacity = capacity;
    hmap->size = 0;
    hmap->cells = calloc(capacity, sizeof(KVStack));

    hmap->hasher = hasher ? hasher : defaultHash;
    hmap->deleter = deleter ? deleter : defaultDelete;
}

void destructHashmap(struct Hashmap *hmap) {
    for (size_t i = 0; i < hmap->capacity; ++i) {
        KVStack *cell = hmap->cells + i;
        while (*cell) {
            struct KeyVal kv = popKVStack(cell);
            free(kv.key);
            hmap->deleter(kv.value);
        }
    }

    free(hmap->cells);
}

void *resetHashmap(struct Hashmap *hmap, size_t keySize, const char *key, void *value) {
    size_t h = hmap->hasher(keySize, key);
    size_t index = h % hmap->capacity;
    for (KVStack cell = hmap->cells[index]; cell; cell = cell->next)
        if (keySize == cell->kv.keySize && strncmp(key, cell->kv.key, keySize) == 0) {
            void *oldValue = cell->kv.value;
            cell->kv.value = value;
            return oldValue;
        }

    if (hmap->size + 1 > hmap->capacity) {
        resizeHashmap(hmap, hmap->capacity * 2);
        index = h % hmap->capacity;
    }

    struct KeyVal kv = {keySize, NULL, value};
    kv.key = malloc(keySize);
    memcpy(kv.key, key, keySize);
    pushKVStack(hmap->cells + index, kv);

    ++(hmap->size);

    return NULL;
}

void *popHashmap(struct Hashmap *hmap, size_t keySize, const char *key) {
    KVStack *cellptr = hmap->cells + (hmap->hasher(keySize, key) % hmap->capacity);
    KVStack *kvs = findKVStack(cellptr, keySize, key);
    if (!kvs)
        return NULL;

    struct KeyVal kv = popKVStack(kvs);
    free(kv.key);
    
    --(hmap->size);

    return kv.value;
}

void *getHashmap(const struct Hashmap *hmap, size_t keySize, const char *key) {
    KVStack cell = hmap->cells[hmap->hasher(keySize, key) % hmap->capacity];
    KVStack *kvs = findKVStack(&cell, keySize, key);
    if (*kvs)
        return (*kvs)->kv.value;
    return NULL;
}

void resizeHashmap(struct Hashmap *hmap, size_t newCapacity) {
    KVStack *newCells = calloc(newCapacity, sizeof(KVStack));

    for (size_t i = 0; i < hmap->capacity; ++i) {
        KVStack cell = hmap->cells[i];
        while (cell) {
            struct KeyVal kv = popKVStack(&cell);
            size_t index = hmap->hasher(kv.keySize, kv.key) % newCapacity;
            pushKVStack(newCells + index, kv);
        }
    }

    free(hmap->cells);
    hmap->cells = newCells;
}

// auxillary functions

// TODO: Improve the default hash function
size_t defaultHash(size_t size, const char *value) {
    size_t res = 0;
    for (size_t i = 0; i < size; ++i)
        res += i * value[i];
    return res;
}

void defaultDelete(void *value) {}