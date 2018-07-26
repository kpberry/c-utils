#ifndef ARRAY_LIST_H
    #define ARRAY_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include "array_list.h"

typedef void (*array_list_free_func)(void*);
typedef int (*array_list_comp_func)(const void*, const void*);

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
    array_list_free_func free_func;
} ARRAY_LIST;

typedef enum {
    SUCCESS,
    NULL_ARRAY_LIST,
    NULL_FREE_FUNC,
    NULL_COMP_FUNC,
    NULL_OUT,
    OUT_OF_BOUNDS,
    ALLOCATION_FAILURE,
    KEY_NOT_FOUND,
    EMPTY_ARRAY_LIST
} ARRAY_LIST_STATUS;

ARRAY_LIST* array_list_new(size_t capacity, array_list_free_func free_func);
ARRAY_LIST_STATUS array_list_free(ARRAY_LIST* al);

ARRAY_LIST_STATUS array_list_insert(ARRAY_LIST* al, void* data, int index);
ARRAY_LIST_STATUS array_list_add(ARRAY_LIST* al, void* data);
ARRAY_LIST_STATUS array_list_push(ARRAY_LIST* al, void* data);

ARRAY_LIST_STATUS array_list_remove(ARRAY_LIST* al, int index, void** out);
ARRAY_LIST_STATUS array_list_pop(ARRAY_LIST* al, void** out);

ARRAY_LIST_STATUS array_list_get(ARRAY_LIST* al, int index, void** out);

ARRAY_LIST_STATUS array_list_sort(ARRAY_LIST* al, int (*comp) (const void*, const void*));
ARRAY_LIST_STATUS array_list_bsearch(ARRAY_LIST* al, const void* key, int (*comp) (const void*, const void*), void** out);


#endif