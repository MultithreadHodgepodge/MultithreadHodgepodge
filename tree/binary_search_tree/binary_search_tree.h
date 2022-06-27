/*
* insert_binary_search_tree()-binary search tree insert function
* @tree: A pointer to pointer to tree 
* @value: value to be insert
*/
void insert_binary_search_tree(tree_t **tree, void *value){
    // Check if it is root node
    if((*tree)->parent==(*tree)){
        (*tree)->value=value;
        (*tree)->left=(*tree)->right=(*tree)->parent=NULL;
        return;
    }
    tree_t *temp=NULL;
    create_tree(&temp);
    temp->value=value;
    temp->left=temp->right=NULL;
    insert_bst_traversal(tree,temp);
}

/*
* insert_bst_traverse()-binary search tree traversal for finding insert place
* @tree: A pointer to pointer to tree 
* @node: tree node to be insert
*/
void insert_bst_traversal(tree_t **tree, tree_t *node){
    if(node->value<(*tree)->value){
        (*tree)->left==NULL? (*tree)->left= node :  insert_bst_traversal(&(*tree)->left,node);
    }
    else{
        (*tree)->right==NULL? (*tree)->right= node :  insert_bst_traversal(&(*tree)->right,node);
    }
}