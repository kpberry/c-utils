#include <stdlib.h>
#include <stdio.h>
#include "array_list.h"

static int int_compar(const void* a, const void* b) {
    return **(int**)b - **(int**) a;
}

int main() {
    ARRAY_LIST* al = array_list_new(10, free);
    printf("%lu, %lu\n", al->size, al->capacity);
    for (int i = 0; i < 100; i++) {
        int* q = (int*) malloc(sizeof(int));
        *q = 100 - i;
        array_list_add(al, q);
    }
    for (int i = 0; i < al->capacity; i++) {
        int* data;
        if (array_list_get(al, i, (void**) &data) == SUCCESS) {
            printf("%d, ", *data);
        } else {
            printf("Access out of bounds.\n");
        }
    }

    for (int i = 3; i < 210; i += 6) {
    	int* data = (int*) malloc(sizeof(int));
        *data = i;
        if (array_list_insert(al, data, i) == SUCCESS) {
        	printf("%d, ", *data);
        } else {
        	printf("Access out of bounds.\n");
        	free(data);
        }
    }

    array_list_sort(al, int_compar);
    int* data;
    int twenty = 20;
    if (array_list_bsearch(al, (const void**) &twenty, 
    	                   int_compar, (void**) &data) == SUCCESS) {
    	printf("%d\n", *data);
    } else {
    	printf("20 not found\n");
    }
    
    for (int i = 0; i < al->size; i++) {
    	printf("%d, ", *(int*) al->data[i]);
    }

    for (int i = 160; i >= 10; i--) {
        int* data;
        if (array_list_remove(al, i, (void**) &data) == SUCCESS) {
            printf("%d, %lu, %lu\n", *data, al->size, al->capacity);
            free(data);
        } else {
            printf("Index %d out of bounds. \n", i);
        }
    }

    array_list_free(al);
    printf("All tests passed.\n");
}