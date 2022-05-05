/*
Implementation of binary tree function
*/
/*
* calculate height of tree
* @tree :pointer to tree 
*/
int height(tree_t* tree)
{
    if (!tree )
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(tree->left);
        int rheight = height(tree->right);
 
        /* use the larger one */
        if (lheight < rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

/*
* binarytree insert function
* @tree: A pointer to pointer to tree 
* @value: value to be insert
*/
void insert_binary_tree(tree_t **tree,void *value){
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

    int h=height(*tree),i=0;
    for(i=0;i<h;i++){
        insert_node_traverse(tree,temp,i);
    }
    
}

/*
* binarytree levelorder traversal for finding insert place
* @tree: A pointer to pointer to tree 
* @tree_node: tree node to be insert
* @height: current height
*/
void insert_node_traverse(tree_t **tree,tree_t *tree_node,int height){
    if((*tree)==NULL) return;
    if(!((*tree)->left)){
        (*tree)->left=tree_node;
        tree_node->parent=(*tree)->left;
        return;
    }
    else if(!((*tree)->right)){
        (*tree)->right=tree_node;
        tree_node->parent=(*tree)->right;
        return;
    }
    if (height==0) return;
    else{
        insert_node_traverse((*tree)->left,tree_node,height-1);
        insert_node_traverse((*tree)->right,tree_node,height-1);
    }

}