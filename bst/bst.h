#ifndef BST_H
	#define BST_H

#include <stdbool.h>

typedef int (*bst_comp_fn)(const void*, const void*);
typedef void (*bst_free_fn)(void*);
typedef void (*bst_consumer_fn)(void*);

typedef struct bst_node {
	struct bst_node* left;
	struct bst_node* right;
	void* data;
} BST_NODE;

typedef struct {
	BST_NODE* root;
	bst_comp_fn comp;
	bst_free_fn free;
	int size;
} BST;

typedef enum {
	SUCCESS,
	MALLOC_FAILURE,
	NULL_BST,
	NULL_TRAVERSAL_FUNCTION
} BST_STATUS;

BST* bst_new(bst_comp_fn comp, bst_free_fn bst_free);
BST_STATUS bst_free(BST* bst);
BST_STATUS bst_add(BST* bst, void* data);
BST_STATUS bst_contains(BST* bst, void* data, bool* result);
BST_STATUS bst_traverse(BST* bst, bst_consumer_fn consumer);
BST_STATUS bst_preorder_traverse(BST* bst, bst_consumer_fn consumer);
BST_STATUS bst_postorder_traverse(BST* bst, bst_consumer_fn consumer);



#endif