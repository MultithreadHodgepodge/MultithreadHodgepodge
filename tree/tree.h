#include<stdbool.h>
#include<stdlib.h>
typedef struct __tree tree_t;
typedef struct __tree{
    void *value;
    struct __tree *left;
    struct __tree *right;
    struct __tree *parent;
    void (*insert)(tree_t**, void*);
    void (*remove)(tree_t**);
    void (*printtree)(tree_t* );
    void (*freetree)(tree_t **);
}tree_t;
void create_tree(tree_t **);
void set_tree_insert(tree_t **, void (*insert)(tree_t**, void*));
void set_tree_print(tree_t **,void (*printtree)(tree_t* ));
void set_tree_remove(tree_t **,void (*remove)(tree_t** ));
void inorder(tree_t *);
void postorder(tree_t *);
void preorder(tree_t *);
//============Binary_tree============//
void insert_binary_tree(tree_t **,void *);

