#ifndef HASHMAP_H
    #define HASHMAP_H
#include <stdlib.h>

typedef size_t (*hashmap_hash_fn) (void* key);
typedef int (*hashmap_comp_fn) (void* a, void* b);
typedef size_t (*hashmap_mod_fn) (size_t hash);
typedef void (*hashmap_free_fn) (void* key);

typedef struct {
    void* key;
    void* value;
    int distance_from_desired;
} HASHMAP_KV;

typedef struct {
    HASHMAP_KV* data;
    size_t size;
    size_t capacity;
    int max_dist;
    int prime_index;
    double load_factor;
    hashmap_hash_fn hash;
    hashmap_comp_fn comp;
    hashmap_free_fn key_free;
    hashmap_free_fn value_free;
} HASHMAP;

typedef enum {
    NULL_HASH_MAP,
    KEY_NOT_PRESENT,
    REALLOCATION_FAILURE,
    SUCCESS
} HASHMAP_STATUS;

HASHMAP_STATUS hashmap_put(HASHMAP* hm, void* key, void* value);
HASHMAP_STATUS hashmap_get(HASHMAP* hm, void* key, void** out);
HASHMAP_STATUS hashmap_del(HASHMAP* hm, void* key);
HASHMAP_STATUS hashmap_free(HASHMAP* hm);
HASHMAP* hashmap_new(hashmap_hash_fn hash, hashmap_comp_fn comp,
    hashmap_free_fn key_free, hashmap_free_fn value_free);
#endif
