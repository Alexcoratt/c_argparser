#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

// key value pair
struct KeyVal {
    size_t keySize;
    char *key;
    void *value;
};

// single linked list to store key value pairs
struct KVSingleList {
    struct KeyVal kv;
    struct KVSingleList *next;
};

typedef struct KVSingleList *KVStack;

#define EMPTY_KVSTACK NULL

typedef size_t hash_func(size_t, const char *);

struct Hashmap {
    size_t capacity;
    size_t size;
    KVStack *cells;

    hash_func *hash;

    alloc_func *alloc;
    delete_func *delete;
};

hash_func defaultHash;

// if hash_func or delete_func is set NULL the default function is used
void initHashmap(struct Hashmap *, size_t capacity, hash_func *, alloc_func *, delete_func *);
void destructHashmap(struct Hashmap *);

// returns the old value of the key (if it is a new key returns NULL)
void *resetHashmap(struct Hashmap *, size_t keySize, const char *key, const void *value);
void *popHashmap(struct Hashmap *, size_t keySize, const char *key);
void *getHashmap(const struct Hashmap *, size_t keySize, const char *key);

void resizeHashmap(struct Hashmap *, size_t newCapacity);

// auxillary methods
typedef void hashmap_traverse_func(size_t keySize, char *key, void *value);
void traverseHashmap(const struct Hashmap *, hashmap_traverse_func *);

#endif