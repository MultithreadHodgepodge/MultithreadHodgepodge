/*
    This file is for testing list function
*/
#include"list.h"
int main()
{
    
    list_t* new_list=NULL;
    create_list(&new_list);
    list_t *node1=(list_t*)malloc(sizeof(list_t)),*node2=(list_t*)malloc(sizeof(list_t)),*node3=(list_t*)malloc(sizeof(list_t)),*node4=(list_t*)malloc(sizeof(list_t));
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

    free_list(&new_list);
    //list_reverse(&new_list);

}

