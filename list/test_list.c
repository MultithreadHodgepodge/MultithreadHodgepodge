/*
    This file is for testing list function
*/
#include"list.h"
int main()
{
    
    list_t *new_list=NULL, *node1=NULL, *node2=NULL, *node3=NULL, *node4=NULL, *node5=NULL;
    new_list=create_list(new_list);
    node1=create_list(node1);
    node2=create_list(node2);
    node3=create_list(node3);
    node4=create_list(node4);
    node5=create_list(node5);
    list_add_tail(new_list,node1);
    list_add_tail(new_list,node2);
    list_add_tail(new_list,node3);
    
    list_add_tail(new_list,node4);
    
    //list_remove_tail(&new_list);
    //list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    list_remove_tail(new_list);
    list_remove_tail(new_list);
    //list_add_tail(&new_list,(void *)8,bigger);
    
    free_list(new_list);
    
    //list_reverse(&new_list);

}

