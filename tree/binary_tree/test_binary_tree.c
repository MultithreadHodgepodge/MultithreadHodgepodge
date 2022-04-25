#include"binary_tree.h"
int main(){
    binary_tree_t *binary_tree=NULL;
    create_binary_tree(&binary_tree);
    set_tree_insert(&(binary_tree->tree),insert_binary_tree);
    

}