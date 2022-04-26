#include"binary_tree.h"

void create_binary_tree(binary_tree_t **binary_tree){
    *binary_tree=(binary_tree_t *)malloc(sizeof(binary_tree_t));

    create_tree(&((*binary_tree)->tree));
    (*binary_tree)->tree->parent=(*binary_tree)->tree;
}
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

// TODO: Not finished yet
void insert_binary_tree(tree_t **tree,void *value){
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
        level_order(tree,temp,i);
    }
    
    
}
void level_order(tree_t **tree,tree_t *tree_node,int height){
    if((*tree)==NULL) return;
    if(!((*tree)->left)){
        (*tree)->left=tree_node;
        return;
    }
    else if(!((*tree)->right)){
        (*tree)->right=tree_node;
        return;
    }
    if (height==0) return;
    else{
        level_order((*tree)->left,tree_node,height-1);
        level_order((*tree)->right,tree_node,height-1);
    }
}

void inorder(tree_t *tree){
    if(tree==NULL) return;
    inorder(tree->left);
    printf("Tree Node: %p\n",tree->value);
    inorder(tree->right);
}