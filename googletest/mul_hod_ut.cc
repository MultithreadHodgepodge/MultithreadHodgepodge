#include <gtest/gtest.h>
#include <iostream>
using namespace std;
extern "C"
{
    #include "../list/list.h"
    #include "../list/stack/stack.h"
}

/*
Test list_h
*/
//create_list()
TEST(createlisttestcase, createlist){
    cout<< "<<Test create_list>>: Start\n"; 
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    EXPECT_NE(new_list,nullptr);
    EXPECT_EQ(new_list->prev,new_list);
    EXPECT_EQ(new_list->next,new_list);
}

//list_add_head()
TEST(listaddheadcase, listaddhead){
    cout<< "<<Test list_add_head>>: Start\n";
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_add_head(&new_list,node1);
    EXPECT_EQ(new_list,node1);
}

//list_add_tail()
TEST(listaddtailcase, listaddtail){
    cout<< "<<Test list_add_tail>>: Start\n";
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_add_tail(new_list,node1);
    EXPECT_EQ(new_list->prev,node1);
    EXPECT_EQ(new_list, node1->next);
}

//list_remove_head()
TEST(listremoveheadcase,listremovehead){
    cout<< "<<Test list_remove_head>>: Start\n";
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_add_tail(new_list,node1);
    list_t *temp=new_list->next;
    list_remove_head(&new_list);
    EXPECT_EQ(new_list,temp);
}

//list_remove_tail()
TEST(listremovetailcase,listremovetail){
    cout<< "<<Test list_remove_tail>>: Start\n";
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_t *node2=MALLOC_LIST()
    list_add_tail(new_list,node1);
    list_add_tail(new_list,node2);
    list_t *temp=new_list->prev->prev;
    list_remove_tail(&new_list);
    EXPECT_EQ(new_list,temp->next);
}

//free_list()
TEST(freelistcase,freelist){
    cout<< "<<Test free_list>>: Start\n";
    list_t* new_list=NULL;
    new_list=create_list(new_list);
    list_t *node1=MALLOC_LIST()
    list_t *node2=MALLOC_LIST()
    list_add_tail(new_list,node1);
    list_add_tail(new_list,node2);
    free_list(&new_list);
    EXPECT_EQ(new_list,nullptr);
}

/*
Test mul_stack_t
*/
//create_stack()
TEST(createstackcase,createstack){
    cout<< "<<Test create_stack>>: Start\n"; 
    mul_stack_t *stack=NULL;
    stack=create_stack(stack,10);
    EXPECT_NE(stack,nullptr);
    EXPECT_EQ(stack->capacity,10);
}

//push()
TEST(pushcase,push){
    mul_stack_t *stack=NULL;
    stack=create_stack(stack,10);
    
}