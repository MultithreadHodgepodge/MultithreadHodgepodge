/*
    This file is for testing list function
*/
#include"list.h"
int main()
{
    int compare(const void *a, const void *b) {
        return *(int *)a -*(int *)b;
    }
    list_t* new_list=NULL;
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)2);
    
    list_add_tail(&new_list,(void *)1);
    
    //list_remove_tail(&new_list);
    //list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    // list_remove_tail(&new_list);
    list_add_before_larger(&new_list,(void *)8);

    print_list(&new_list);
    //list_reverse(&new_list);

}

