#include"../tree.h"
#include"binary_search_tree.h"
int main(){
    tree_t *tree=NULL;
    create_tree(&tree);
    set_tree_insert(&tree,insert_binary_search_tree);
    set_tree_print(&tree,inorder);
    set_tree_remove(&tree,remove_binary_search_tree_interface);
    tree->insert(&tree,4);
    tree->insert(&tree,5);
    tree->insert(&tree,1);
    tree->insert(&tree,2);
    tree->insert(&tree,3);
    tree->remove(&tree,3);
    find_bst(&tree,5);
    tree->printtree(tree);
}