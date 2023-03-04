/*
    This file is for testing list function
*/
#include"list.h"
int main()
{
    
    list_t* new_list=NULL;
    list_remove_tail(&new_list);
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_t *node2=MALLOC_LIST()
    list_t *node3=MALLOC_LIST()
    list_t *node4=MALLOC_LIST()
    list_t *node5=MALLOC_LIST()
    list_add_tail(new_list,node1);
    list_add_tail(new_list,node2);
    list_add_tail(new_list,node3);
    
    list_add_tail(new_list,node4);
    
    //list_remove_tail(&new_list);
    //list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    //list_add_tail(&new_list,(void *)8,bigger);
    list_remove_specific_node(new_list,node3);
    
    free_list(&new_list);
    
    //list_reverse(&new_list);

}

