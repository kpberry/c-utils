#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/resource.h>
#include "hashmap.h"


int int_comp(void* a, void* b) {
	int ia = *(int*) a;
	int ib = *(int*) b;
	return ia - ib;
}

size_t int_hash(void* key) {
	return *(int*) key;
}

void noop(void* v) {}

int main() {
	struct rlimit limit;

	getrlimit(RLIMIT_STACK, &limit);
	printf ("Stack Limit: %ld\n", limit.rlim_cur);

	int size = 100000000;
	printf("Size: %d\n", size);
	printf("If you want to test truly big sizes, call `ulimit -s unlimited`\n");

	HASHMAP* hm = hashmap_new(int_hash, int_comp, noop, noop);

	int* ints = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		ints[i] = 30 - i + i * i;
	}

	int* indices = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		indices[i] = i;
		hashmap_put(hm, indices + i, ints + i);
	}	

	for (int i = 0; i < size; i++) {
		int* out;
		hashmap_get(hm, indices + i, (void*) &out);
		assert(*out == 30 - i + i * i);
	}

	hashmap_free(hm);
	free(ints);
	free(indices);
	printf("All tests passed.\n");
}
