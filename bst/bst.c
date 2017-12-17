#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"


BST* bst_new(bst_comp_fn comp, bst_free_fn bst_free) {
    if (!(comp && bst_free)) {
        return NULL;
    }

    BST* result = malloc(sizeof(BST));
    if (result == NULL) {
        return NULL;
    }
    result->root = NULL;
    result->size = 0;
    result->comp = comp;
    result->free = bst_free;
    return result;
}

static void bst_free_recurse(BST* bst, BST_NODE* node);
BST_STATUS bst_free(BST* bst) {
    if (bst == NULL) {
        return SUCCESS;
    }
    bst_free_recurse(bst, bst->root);
    free(bst);
    return SUCCESS;
}

static void bst_free_recurse(BST* bst, BST_NODE* node) {
    if (node != NULL) {
        bst->free(node->data);
        bst_free_recurse(bst, node->left);
        bst_free_recurse(bst, node->right);
        free(node);
    }   
}

// TODO removal, making more things iterative, balancing

BST_STATUS bst_add(BST* bst, void* data) {
    if (bst == NULL) {
        return NULL_BST;
    }

    BST_NODE** current = &bst->root;

    while (*current != NULL) {
        if (bst->comp((*current)->data, data) <= 0) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }

    *current = malloc(sizeof(BST_NODE));
    if (current == NULL) {
        return MALLOC_FAILURE;
    }

    (*current)->left = (*current)->right = NULL;
    (*current)->data = data;

    return SUCCESS;
}

static bool bst_contains_recurse(BST* bst, BST_NODE* node, void* data);
BST_STATUS bst_contains(BST* bst, void* data, bool* result) {
    if (bst == NULL) {
        result = false;
        return NULL_BST;
    }

    *result = bst_contains_recurse(bst, bst->root, data);
    return SUCCESS;
}

static bool bst_contains_recurse(BST* bst, BST_NODE* node, void* data) {
    if (node == NULL) {
        return false;
    } 
    int comp = bst->comp(node->data, data);
    if (comp < 0) {
        return bst_contains_recurse(bst, node->left, data);
    } else if (comp > 0) {
        return bst_contains_recurse(bst, node->right, data);
    } else {
        return true;
    }
}


static void bst_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer);
BST_STATUS bst_traverse(BST* bst, bst_consumer_fn consumer) {
    if (bst == NULL) {
        return NULL_BST;
    }
    if (consumer == NULL) {
        return NULL_TRAVERSAL_FUNCTION;
    } 

    bst_traverse_recurse(bst->root, consumer);
    return SUCCESS;
}

static void bst_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer) {
    if (node != NULL) {
        bst_traverse_recurse(node->left, consumer);
        consumer(node->data);
        bst_traverse_recurse(node->right, consumer);
    }
}

static void bst_preorder_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer);
BST_STATUS bst_preorder_traverse(BST* bst, bst_consumer_fn consumer) {
    if (bst == NULL) {
        return NULL_BST;
    }
    if (consumer == NULL) {
        return NULL_TRAVERSAL_FUNCTION;
    } 

    bst_preorder_traverse_recurse(bst->root, consumer);
    return SUCCESS;
}

static void bst_preorder_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer) {
    if (node != NULL) {
        consumer(node->data);
        bst_preorder_traverse_recurse(node->left, consumer);
        bst_preorder_traverse_recurse(node->right, consumer);
    }
}

static void bst_postorder_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer);
BST_STATUS bst_postorder_traverse(BST* bst, bst_consumer_fn consumer) {
    if (bst == NULL) {
        return NULL_BST;
    }
    if (consumer == NULL) {
        return NULL_TRAVERSAL_FUNCTION;
    } 

    bst_postorder_traverse_recurse(bst->root, consumer);
    return SUCCESS;
}

static void bst_postorder_traverse_recurse(BST_NODE* node, bst_consumer_fn consumer) {
    if (node != NULL) {
        bst_postorder_traverse_recurse(node->left, consumer);
        bst_postorder_traverse_recurse(node->right, consumer);
        consumer(node->data);
    }
}

