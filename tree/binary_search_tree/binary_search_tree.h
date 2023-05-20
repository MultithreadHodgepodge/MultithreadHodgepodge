/**
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

/**
* insert_bst_traverse()-binary search tree traversal for finding insert place
* @tree: A pointer to pointer to tree 
* @node: tree node to be insert
*/
void insert_bst_traversal(tree_t **tree, tree_t *node){
    if(node->value<(*tree)->value){
        (*tree)->left==NULL? (*tree)->left= node :  insert_bst_traversal(&(*tree)->left,node);
        //(*tree)->left==node? node->parent=(*tree)->left: return;
    }
    else{
        (*tree)->right==NULL? (*tree)->right= node :  insert_bst_traversal(&(*tree)->right,node);
        //(*tree)->right==node? node->parent=(*tree)->right: return;
    }
}

/**
* minValueNode()-find min value node
* @tree: A pointer to tree_t 
* Returns: Pointer to min value node
*/
tree_t* minValueNode(tree_t* node)
{
    tree_t* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

/**
* __remove_binary_search_tree()-Delete node function
* @tree: A pointer to pointer to tree_t 
* @value: value to be deleted
* Returns: Pointer to tree_t node
*/
tree_t* __remove_binary_search_tree(tree_t **tree, void *value){
    if(!(*tree)) {printf("Node Value %p not exist in BST!!!!!\n",value); return NULL;}
    if(value<(*tree)->value)(*tree)->left=__remove_binary_search_tree(&(*tree)->left,value);
    else if(value>(*tree)->value)(*tree)->right=__remove_binary_search_tree(&(*tree)->right,value);
    else{
        if((*tree)->left==NULL){
            tree_t *temp=(*tree)->right;
            *tree=NULL;
            free(*tree);
            return temp;
        }
        else if((*tree)->right==NULL){
            tree_t *temp=(*tree)->left;
            *tree=NULL;
            free(*tree);
            return temp;
        }

        tree_t *temp=minValueNode((*tree)->right);
        (*tree)->value=temp->value;
        (*tree)->right=__remove_binary_search_tree(&(*tree)->right,temp->value);
    }
    return *tree;
}

/**
* remove_binary_search_tree_interface()-Delete node function interface(Outter usage)
* @tree: A pointer to pointer to tree_t 
* @value: value to be deleted
*/
//TODO: Remove interface
void remove_binary_search_tree_interface(tree_t **tree, void *value){
    tree_t *temp=__remove_binary_search_tree(tree,value);
}
/**
* find_bst()-Find if specific value is in bst
* @tree: A pointer to pointer to tree_t 
* @value: value to be found
*/
void find_bst(tree_t **tree, void *value){
    if(!(*tree)) return;
    if(value<(*tree)->value){
        find_bst(&(*tree)->left,value);
    }
    else if(value>(*tree)->value){
        find_bst(&(*tree)->right,value);
    }
    else printf("Found %p!!!\n",value);
}