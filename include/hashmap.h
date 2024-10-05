#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"
#include "stack.h"

// key value pair
struct StringPair {
    char *key;
    void *value;
};

struct StringPair *allocStringPair(const struct StringPair *);
void delStringPair(struct StringPair *);

// hashmap definitions
typedef size_t hash_func(size_t, const char *);
hash_func defaultHash;

struct Hashmap {
    size_t capacity;
    size_t size;
    struct Stack *cells; // stack of StringPair *

    hash_func *hash;

    alloc_func *alloc;
    del_func *del;
};

// if hash_func or delete_func is set NULL the default function is used
void initHashmap(struct Hashmap *, size_t capacity, hash_func *, alloc_func *, del_func *);
void destructHashmap(struct Hashmap *);

// returns the old value of the key (if it is a new key returns NULL)
void setHashmap(struct Hashmap *, const char *key, const void *value);
void eraseHashmap(struct Hashmap *, const char *key);
void **getHashmap(const struct Hashmap *, const char *key);

void resizeHashmap(struct Hashmap *, size_t newCapacity);

// auxillary methods
typedef void hashmap_traverse_func(size_t keySize, char *key, void *value);
void traverseHashmap(const struct Hashmap *, hashmap_traverse_func *);

#endif