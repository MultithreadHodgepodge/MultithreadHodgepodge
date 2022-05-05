#include"../tree.h"
#include"binary_tree.h"
int main(){
    /*
    binary_tree_t *binary_tree=NULL;
    create_binary_tree(&binary_tree);
    set_tree_insert(&(binary_tree->tree),insert_binary_tree);
    set_tree_print(&(binary_tree->tree),inorder);
    binary_tree->tree->insert(&binary_tree->tree,1);    
    binary_tree->tree->insert(&binary_tree->tree,2);
    binary_tree->tree->insert(&binary_tree->tree,3);    
    binary_tree->tree->printtree(binary_tree->tree);
    */
   tree_t *tree=NULL;
   create_tree(&tree);
   set_tree_insert(&tree,insert_binary_tree);
   set_tree_print(&tree,inorder);
   tree->insert(&tree,1);
   tree->insert(&tree,2);
   tree->insert(&tree,3);
   tree->printtree(tree);
}