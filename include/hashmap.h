#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"
#include "simple_stack.h"

// key value pair
struct StringPair {
    char *key;
    void *value;
};

struct StringPair *initStringPairPtr(char *key, void *value);
void freeStringPair(struct StringPair *);

// hashmap definitions
typedef size_t (*str_hash_func)(const char *);
size_t defaultStrHash(const char *);

struct Hashmap {
    size_t capacity;
    size_t size;
    sstack *cells; // array of sstack of StringPair *

    str_hash_func hash;

    alloc_func alloc;
    del_func del;
};

// if hash_func or delete_func is set NULL the default function is used
void hm_init(struct Hashmap *, size_t capacity, str_hash_func, alloc_func, del_func);
void hm_free(struct Hashmap *);

// returns the old value of the key (if it is a new key returns NULL)
void hm_set(struct Hashmap *, const char *key, const void *value);
void hm_erase(struct Hashmap *, const char *key);
void **hm_get(const struct Hashmap *, const char *key);

void hm_resize(struct Hashmap *, size_t newCapacity);

// auxillary methods
typedef void (* hm_traverse_func)(char *key, void *value);
void hm_traverse(const struct Hashmap *, hm_traverse_func);

#endif