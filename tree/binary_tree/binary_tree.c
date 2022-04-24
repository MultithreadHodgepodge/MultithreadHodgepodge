#include"binary_tree.h"
#include"../../queue/queue.h"
void create_binary_tree(binary_tree_t **binary_tree){
    (*binary_tree)=(binary_tree_t *)malloc(sizeof(binary_tree_t));
    (*binary_tree)->tree=NULL;

}
int height(struct tree_t* tree)
{
    if (node == NULL)
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
void insert_binary_tree(tree_t **tree,(void *)value){
    if(!(*tree)){
        create_tree(tree);
        
        (*tree)->value=value;
        (*tree)->left=(*tree)->right=(*tree)->parent=NULL;
        return;
    }

    tree_t *cur=(*tree);
    tree_t *temp;
    create_tree(temp);
    temp->value=value;
    temp->left=temp->right=NULL;
    queue_t *queue;
    while(cur){

    }
    
    
}