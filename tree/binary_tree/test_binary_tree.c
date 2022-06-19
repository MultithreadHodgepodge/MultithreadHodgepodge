#include"../tree.h"
#include"binary_tree.h"
int main(){

    tree_t *tree=NULL;
    create_tree(&tree);
    set_tree_insert(&tree,insert_binary_tree);
    set_tree_print(&tree,inorder);
    set_tree_remove(&tree,remove_binary_tree);
    tree->insert(&tree,1);
    tree->insert(&tree,2);
    tree->insert(&tree,3);
    tree->insert(&tree,4);
    tree->insert(&tree,5);
    tree->insert(&tree,6);
    tree->printtree(tree);
    tree->remove(&tree);
    tree->printtree(tree);
}