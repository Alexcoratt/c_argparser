#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "common.h"

void pushKVStack(KVStack *kvs, struct KeyVal kv) {
    KVStack newItem = T_MALLOC(struct KVSingleList);
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

// TODO: Improve the default hash function
size_t defaultHash(size_t size, const char *value) {
    size_t res = 0;
    for (size_t i = 0; i < size; ++i)
        res += i * value[i];
    return res;
}

// definitions of hashmap methods
void initHashmap(struct Hashmap *hmap, size_t capacity, hash_func *hash, alloc_func *alloc, delete_func *delete) {
    hmap->capacity = capacity;
    hmap->size = 0;
    hmap->cells = T_CALLOC(KVStack, capacity);

    hmap->hash = hash ? hash : defaultHash;

    hmap->alloc = alloc;
    hmap->delete = delete ? delete : defaultDelete;
}

void destructHashmap(struct Hashmap *hmap) {
    for (size_t i = 0; i < hmap->capacity; ++i) {
        KVStack *cell = hmap->cells + i;
        while (*cell) {
            struct KeyVal kv = popKVStack(cell);
            free(kv.key);
            hmap->delete(kv.value);
        }
    }

    free(hmap->cells);
}

void *resetHashmap(struct Hashmap *hmap, size_t keySize, const char *key, const void *value) {
    size_t h = hmap->hash(keySize, key);
    size_t index = h % hmap->capacity;
    for (KVStack cell = hmap->cells[index]; cell; cell = cell->next)
        if (keySize == cell->kv.keySize && strncmp(key, cell->kv.key, keySize) == 0) {
            void *oldValue = cell->kv.value;
            cell->kv.value = hmap->alloc(value);
            return oldValue;
        }

    if (hmap->size + 1 > hmap->capacity) {
        resizeHashmap(hmap, hmap->capacity * 2);
        index = h % hmap->capacity;
    }

    struct KeyVal kv = {keySize, malloc(keySize), hmap->alloc(value)};
    memcpy(kv.key, key, keySize);
    pushKVStack(hmap->cells + index, kv);

    ++(hmap->size);

    return NULL;
}

void *popHashmap(struct Hashmap *hmap, size_t keySize, const char *key) {
    KVStack *cellptr = hmap->cells + (hmap->hash(keySize, key) % hmap->capacity);
    KVStack *kvs = findKVStack(cellptr, keySize, key);
    if (!kvs)
        return NULL;

    struct KeyVal kv = popKVStack(kvs);
    free(kv.key);
    
    --(hmap->size);

    return kv.value;
}

void *getHashmap(const struct Hashmap *hmap, size_t keySize, const char *key) {
    KVStack cell = hmap->cells[hmap->hash(keySize, key) % hmap->capacity];
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
            size_t index = hmap->hash(kv.keySize, kv.key) % newCapacity;
            pushKVStack(newCells + index, kv);
        }
    }

    free(hmap->cells);
    hmap->cells = newCells;
}

void traverseHashmap(const struct Hashmap *hmap, hashmap_traverse_func *func) {
    for (size_t i = 0; i < hmap->capacity; ++i)
        for (KVStack iter = hmap->cells[i]; iter; iter = iter->next)
            func(iter->kv.keySize, iter->kv.key, iter->kv.value);
}