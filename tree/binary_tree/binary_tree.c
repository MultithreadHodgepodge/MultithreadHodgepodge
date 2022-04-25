#include"binary_tree.h"

void create_binary_tree(binary_tree_t **binary_tree){
    *binary_tree=(binary_tree_t *)malloc(sizeof(binary_tree_t));

    create_tree(&((*binary_tree)->tree));
    (*binary_tree)->tree->head=true;
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
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

// TODO: Not finished yet
void insert_binary_tree(tree_t **tree,void *value){
    if((*tree)->head){
        (*tree)->value=value;
        (*tree)->left=(*tree)->right=(*tree)->parent=NULL;
        return;
    }


    tree_t *temp;
    create_tree(temp);
    temp->value=value;
    temp->left=temp->right=NULL;

    int h=height(*tree),i=0;
    for(i=1;i<=h;i++){
        level_order(tree,temp,h);
    }
    
    
}
void level_order(tree_t **tree,tree_t *tree_node,int height){
    if(!*tree) return;
    if(!((*tree)->left)){
        (*tree)->left=tree_node;
        return;
    }
    else if(!((*tree)->right)){
        (*tree)->right=tree_node;
        return;
    }
    if (height==1) return;
    else{
        level_order((*tree)->left,tree_node,height-1);
        level_order((*tree)->right,tree_node,height-1);
    }
}