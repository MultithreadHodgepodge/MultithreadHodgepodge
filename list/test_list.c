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
    list_add_tail(&new_list,(void *)4);
    print_list(&new_list);
    list_remove_tail(&new_list);
    print_list(&new_list);
    list_remove_tail(&new_list);
    print_list(&new_list);
    free_list(&new_list);
    
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)4);

    free_list(&new_list);
    free_list(&new_list);
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)4);
    list_add_tail(&new_list,(void *)4);
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)4);
    
    list_add_tail(&new_list,(void *)30);
    list_add_tail(&new_list,(void *)20);
    list_add_tail(&new_list,(void *)7);
    list_add_tail(&new_list,(void *)4);
    sort(&new_list, compare);
    print_list(&new_list);
    free_list(&new_list);
}

