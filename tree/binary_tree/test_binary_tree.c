#include"../tree.h"
#include"binary_tree.h"
int main(){

    tree_t *tree=NULL;
    create_tree(&tree);
    set_tree_insert(tree,insert_binary_tree);
    set_tree_print(tree,inorder);
    set_tree_remove(tree,remove_binary_tree);
    tree->insert(&tree, (void*)4);
    tree->insert(&tree, (void*)5);
    tree->insert(&tree, (void*)1);
    tree->insert(&tree, (void*)2);
    tree->insert(&tree, (void*)3);
    tree->insert(&tree, (void*)6);
    tree->printtree(tree);
    tree->remove(&tree, (void*)3);
    tree->printtree(tree);
    free_tree(&tree);

}