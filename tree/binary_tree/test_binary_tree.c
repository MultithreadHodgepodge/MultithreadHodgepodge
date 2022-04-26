#include"binary_tree.h"
int main(){
    binary_tree_t *binary_tree=NULL;
    create_binary_tree(&binary_tree);
    set_tree_insert(&(binary_tree->tree),insert_binary_tree);
    set_tree_print(&(binary_tree->tree),inorder);
    binary_tree->tree->insert(&binary_tree->tree,1);    
    binary_tree->tree->insert(&binary_tree->tree,2);
    binary_tree->tree->insert(&binary_tree->tree,3);    
    binary_tree->tree->printtree(binary_tree->tree);

}