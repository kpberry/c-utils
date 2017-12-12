#include <stdlib.h>
#include "array_list.h"

ARRAY_LIST* array_list_new(size_t capacity, array_list_free_func free_func) {
	ARRAY_LIST* result = (ARRAY_LIST*) malloc(sizeof(ARRAY_LIST));
	if (result == NULL) {
		return NULL;
	}
	result->size = 0;
	result->capacity = capacity > 0 ? capacity : 1;
	result->free_func = free_func == NULL ? free : free_func;
	result->data = (void**) malloc(capacity * sizeof(void*));
	if (result->data == NULL) {
		free(result);
		return NULL;
	}	
	return result;
}

ARRAY_LIST_STATUS array_list_free(ARRAY_LIST* al) {
	if (al == NULL) {
		return NULL_ARRAY_LIST;
	}
	if (al->free_func == NULL) {
		return NULL_FREE_FUNC;
	}
	for (int i = 0; i < al->size; i++) {
		al->free_func(al->data[i]);
	}
	free(al->data);
	free(al);
	return SUCCESS;
}

ARRAY_LIST_STATUS array_list_insert(ARRAY_LIST* al, void* data, int index) {
	if (al == NULL) {
		return NULL_ARRAY_LIST;
	} else if (index < 0 || index > al->size) {
		return OUT_OF_BOUNDS;
	}

	if (al->size == al->capacity) {
		size_t new_cap = al->capacity << 1;
		void** temp = (void**) realloc(al->data, new_cap * sizeof(void*));
		if (temp == NULL) {
			return ALLOCATION_FAILURE;
		} else {
			al->capacity = new_cap;
			al->data = temp;
		}
	}

	for (int i = al->size; i > index; i--) {
		al->data[i] = al->data[i - 1];
	}

	al->data[index] = data;
	al->size++;
	return SUCCESS;
}

ARRAY_LIST_STATUS array_list_add(ARRAY_LIST* al, void* data) {
	return array_list_insert(al, data, al->size);
}

ARRAY_LIST_STATUS array_list_push(ARRAY_LIST* al, void* data) {
	return array_list_add(al, data);
}

ARRAY_LIST_STATUS array_list_pop(ARRAY_LIST* al, void** out) {
	return array_list_remove(al, al->size, out);
}

ARRAY_LIST_STATUS array_list_get(ARRAY_LIST* al, int index, void** out) {
	if (out == NULL) {
		return NULL_OUT;
	} else if (al == NULL) {
		*out = NULL;
		return NULL_ARRAY_LIST;
	} else if (index >= al->size) {
		*out = NULL;
		return OUT_OF_BOUNDS;
	} else {
		*out = al->data[index];
		return SUCCESS;
	}
}

ARRAY_LIST_STATUS array_list_remove(ARRAY_LIST* al, int index, void** out) {
	if (out == NULL) {
		return NULL_OUT;
	} else if (al == NULL) {
		*out = NULL;
		return NULL_ARRAY_LIST;
	} else if (index >= al->size) {
		*out = NULL;
		return OUT_OF_BOUNDS;
	} else if (al->size <= 0) {
		*out = NULL;
		return EMPTY_ARRAY_LIST;
	}

	*out = al->data[index];
	al->size--;
	for (int i = index; i < al->size; i++) {
		al->data[i] = al->data[i + 1];
	}

	if (al->size <= al->capacity >> 2) {
		size_t new_cap = al->capacity >> 1;
		void** temp = (void**) realloc(al->data, new_cap * sizeof(void*));
		if (temp == NULL) {
			return ALLOCATION_FAILURE;
		} else {
			al->capacity = new_cap;
			al->data = temp;
		}
	}

	return SUCCESS;
}

ARRAY_LIST_STATUS array_list_sort(ARRAY_LIST* al, array_list_comp_func comp) {
	if (al == NULL) {
		return NULL_ARRAY_LIST;
	} else if (comp == NULL) {
		return NULL_COMP_FUNC;
	}
	qsort(al->data, al->size, sizeof(void*), comp);
	return SUCCESS;
}

ARRAY_LIST_STATUS array_list_bsearch(ARRAY_LIST* al, const void* key, 
									 array_list_comp_func comp, void** out) {
	if (al == NULL) {
		return NULL_ARRAY_LIST;
	} else if (comp == NULL) {
		return NULL_COMP_FUNC;
	} else if (out == NULL) {
		return NULL_OUT;
	}
	*out = *(void**) bsearch(&key, al->data, al->size, sizeof(void*), comp);
	if (*out == NULL) {
		return KEY_NOT_FOUND;
	} else {
		return SUCCESS;
	}
}
