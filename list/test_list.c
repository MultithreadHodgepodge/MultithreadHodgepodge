/*
    This file is for testing list function
*/
#include"list.h"
int main(){
    list_t* new_list=NULL;
    list_add_tail(&new_list,(void *)3);
    list_add_tail(&new_list,(void *)4);
    list_remove_tail(&new_list);
    list_remove_tail(&new_list);
    print_list(new_list);
    free_list(new_list);

}