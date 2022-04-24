#include"tree.h"
/*
* Create empty tree
* @tree: A pointer to pointer which point to tree 
*/
void create_tree(tree_t **tree){
    if (*tree) {
        printf("Tree Exist\n");
        return;
    } 
    printf("Tree Creation\n");
    (*tree)=(tree_t)malloc(sizeof(tree_t));
    
}

void set_tree_insert(tree_t **tree, void (*insert)(tree_t**, void*)){
    (*tree)->insert=insert;
}