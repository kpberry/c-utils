#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void print_int(void* pa) {
    printf("%d\n", *(int*) pa);
}

int int_comp(const void* a, const void* b) {
    return *(int*) b - *(int*) a;
}

void noop(void* a) {}

int main() {
    BST* bst = bst_new(int_comp, noop);
    int size = 10;
    int* ints = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        ints[i] = random();
        bst_add(bst, ints + i);
    }

    bst_traverse(bst, print_int);
    bst_free(bst);
    free(ints);
}