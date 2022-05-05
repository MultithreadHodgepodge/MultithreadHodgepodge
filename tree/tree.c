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
    (*tree)=(tree_t *)malloc(sizeof(tree_t));
    (*tree)->parent=(*tree);//parent will be changed while inserting
}
/*
* set tree insert function
* @tree: A pointer to pointer which point to tree 
* @insert: function pointer point to function
*/
void set_tree_insert(tree_t **tree, void (*insert)(tree_t**, void*)){
    (*tree)->insert=insert;
}
/*
* set tree print function
* @tree: A pointer to pointer which point to tree 
* @insert: function pointer point to function
*/
void set_tree_print(tree_t **tree, void (*printtree)(tree_t*)){
    (*tree)->printtree=printtree;
}
/*
* tree inorder traversal function
* @tree: A pointer to tree 
*/
void inorder(tree_t *tree){
    if(tree==NULL) return;
    printf("Tree Node: %p\n",tree->value);
    inorder(tree->left);
    inorder(tree->right);
}

/*
* tree preorder traversal function
* @tree: A pointer to tree 
*/
void preorder(tree_t *tree){
    if(tree==NULL) return;
    inorder(tree->left);
    printf("Tree Node: %p\n",tree->value);
    inorder(tree->right);
}


/*
* tree postorder traversal function
* @tree: A pointer to tree 
*/
void postorder(tree_t *tree){
    if(tree==NULL) return;
    inorder(tree->left);
    inorder(tree->right);
    printf("Tree Node: %p\n",tree->value);
    
}

