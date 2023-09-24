#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include <stdint.h>
#ifndef LIST_H__
#include "../common/common_struct.h"
#endif

#include "../common/mul_hodgepodge_assert.h"

#ifndef TREE_H__
#define TREE_H__
typedef struct __tree{
    void *value;
    struct __tree *left;
    struct __tree *right;
    struct __tree *parent;
    void (*insert)(struct __tree*, void*);
    void (*remove)(struct __tree**, void*);
    void (*printtree)(struct __tree* );
    state st;
}tree_t;
#endif
#if defined(MUL_HOD_UT) 
    extern tree_t *create_tree(tree_t *);
    extern void set_tree_insert(tree_t *, void (*insert)(tree_t*, void*));
    extern void set_tree_print(tree_t *,void (*printtree)(tree_t* ));
    extern void set_tree_remove(tree_t *,void (*remove)(tree_t**, void* ));
    extern void inorder(tree_t *);
    extern void postorder(tree_t *);
    extern void preorder(tree_t *);
    extern void free_tree(tree_t **);
#else
    tree_t *create_tree(tree_t *);
    void set_tree_insert(tree_t *, void (*insert)(tree_t*, void*));
    void set_tree_print(tree_t *,void (*printtree)(tree_t* ));
    void set_tree_remove(tree_t *,void (*remove)(tree_t**, void* ));
    void inorder(tree_t *);
    void postorder(tree_t *);
    void preorder(tree_t *);
    void free_tree(tree_t **);
#endif //defined(MUL_HOD_UT)
