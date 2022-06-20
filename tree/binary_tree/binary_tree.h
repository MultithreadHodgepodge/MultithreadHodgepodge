bool insert_node_traverse(tree_t **,tree_t *, int);
/*
Implementation of binary tree function
*/
/*
* height()-calculate height of tree
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
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

/*
* insert_binary_tree()-binarytree insert function
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
    
    for(i=1;i<=h;i++){
        if(insert_node_traverse(tree,temp,i))return;
    }

}

/*
* insert_node_traverse()-binarytree levelorder traversal for finding insert place
* @tree: A pointer to pointer to tree 
* @tree_node: tree node to be insert
* @height: current height
*/
bool insert_node_traverse(tree_t **tree,tree_t *tree_node,int height){
    if((*tree)==NULL) return false;
    if(!((*tree)->left)){
        (*tree)->left=tree_node;
        tree_node->parent=(*tree);
        return true;
    }
    else if(!((*tree)->right)){
        (*tree)->right=tree_node;
        tree_node->parent=(*tree);
        return true;
    }
    if(height==1) return false;
    if(insert_node_traverse(&(*tree)->left,tree_node,height-1)) return true;
    if(insert_node_traverse(&(*tree)->right,tree_node,height-1)) return true;
}

/*
* find_last_node()-find last node in binary tree
* @tree: A pointer to pointer to tree 
* @height: height of binary tree
* @tree_node: tree node to store the last node
*/
void find_last_node(tree_t **tree,int h,tree_t **last_node){
    if((*tree)==NULL ) return;
    if(h==1) {(*last_node)=(*tree);}

    find_last_node(&(*tree)->left,h-1,last_node);
    find_last_node(&(*tree)->right,h-1,last_node);
}
/*
* remove_binary_tree()-remove last node in binary tree
* @tree: A pointer to pointer to tree
*/
void remove_binary_tree(tree_t **tree){
    tree_t *last_node=(tree_t *)malloc(sizeof(tree_t));
    int h=height(*tree);
    find_last_node(tree,h,&last_node);
    printf("Remove node %d\n",last_node->value);
    if(last_node->parent->left==last_node)last_node->parent->left=NULL;
    else if(last_node->parent->right==last_node)last_node->parent->right=NULL;
    free(last_node);
}