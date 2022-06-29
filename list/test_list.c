/*
    This file is for testing list function
*/
#include"list.h"
int main()
{
    
    list_t* new_list=NULL;
    list_add_before_larger_smaller(&new_list,(void *)3,bigger);
    list_add_before_larger_smaller(&new_list,(void *)2,bigger);
    
    list_add_before_larger_smaller(&new_list,(void *)1,bigger);
    
    //list_remove_tail(&new_list);
    //list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    list_add_before_larger_smaller(&new_list,(void *)8,bigger);

    print_list(&new_list);
    free_list(&new_list);
    //list_reverse(&new_list);

}

