#include "../tree.h"
#include <stdio.h>
#include<stdlib.h>
typedef struct __binary_tree{
    tree_t *tree;
}binary_tree_t;

void create_binary_tree(binary_tree_t **);
void insert_binary_tree(tree_t **,void *value);
void inorder(tree_t *);
void preorder(tree_t *);
void postorder(tree_t *);
void delete_last(tree_t *);