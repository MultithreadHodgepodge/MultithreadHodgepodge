#include"../tree.h"
#include"binary_search_tree.h"
int main(){
    tree_t *tree=NULL;
    create_tree(&tree);
    set_tree_insert(&tree,insert_binary_search_tree);
    set_tree_print(&tree,inorder);
    tree->insert(&tree,4);
    tree->insert(&tree,5);
    tree->insert(&tree,1);
    tree->insert(&tree,2);
    tree->insert(&tree,3);
    tree->printtree(tree);
}