#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef void (*delete_func)(void *);
typedef size_t (*hash_func)(size_t, const char *);

struct KVSinglist;
typedef struct KVSinglist *KVStack;

struct Hashmap {
    size_t capacity;
    size_t size;
    KVStack *cells;

    hash_func hasher;
    delete_func deleter;
};

// if hash_func or delete_func is set NULL the default function is used
void initHashmap(struct Hashmap *, size_t capacity, hash_func, delete_func);

void destructHashmap(struct Hashmap *);

// returns the old value of the key (if it is a new key returns NULL)
void *resetHashmap(struct Hashmap *, size_t keySize, const char *key, void *value);
void *popHashmap(struct Hashmap *, size_t keySize, const char *key);

// returns pointer to the value if the key exists otherwise returns NULL
void **getHashmap(struct Hashmap *, size_t keySize, const char *key);
void *getConstHashmap(const struct Hashmap *, size_t keySize, const char *key); // not ready yet

#endif