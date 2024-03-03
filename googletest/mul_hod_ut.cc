#include <gtest/gtest.h>
#include <iostream>
using namespace std;
extern "C"
{
    #include "../list/list.h"
    #include "../list/stack/stack.h"
    #include "../list/queue/queue.h"
    #include "../list/hashtable/hashtable.h"
    #include "../tree/tree.h"
    #include "../tree/binary_search_tree/binary_search_tree.h"
}

/*
Test list_t
*/
TEST( TESTLIST, list_test ){
    cout<< "<<Test list_t>>: Start\n"; 
    list_t *new_list = NULL;
    new_list = create_list( new_list );
    EXPECT_NE( new_list, nullptr );
    EXPECT_EQ( new_list->prev, new_list );
    EXPECT_EQ( new_list->next, new_list );
    EXPECT_EQ( new_list->st.bit.configured, 1 );
    EXPECT_EQ( new_list->st.bit.is_malloc, 1 );
    EXPECT_EQ( new_list->st.bit.is_free, 0 );
    EXPECT_EQ( new_list->st.bit.is_multithread, 0 );
    /*************************************************************
     *  Test list 1_1: 
     *  Create one node, remove one with list_remove_head
    **************************************************************/
    cout<< "<<Test list case 1_1>>: Start\n";
    list_t *new_head = list_remove_head( new_list );
    EXPECT_EQ( new_head, nullptr );

    /*************************************************************
     *  Test list 1_2: 
     * Create one node, add one with list_add_head , remove one with list_remove_tail
    **************************************************************/
    cout<< "<<Test list case 1_2>>: Start\n";
    new_list = create_list( new_list );
    list_t *temp = new_list, *node1 = NULL;
    node1 = create_list( node1 );
    list_add_head( &new_list, node1 );
    EXPECT_EQ( temp->prev, new_list );
    EXPECT_EQ( temp->next, new_list );
    EXPECT_EQ( temp, new_list->prev );
    EXPECT_EQ( temp, new_list->next );
    list_remove_tail( new_list );
    EXPECT_EQ( new_list->prev, new_list );
    EXPECT_EQ( new_list->next, new_list );

    /*************************************************************
     *  Test list 1_3: 
     * Create one node, add two node
     * one with list_add_head , another with list_add_tail 
     * remove two, one with list_remove_tail, another with list_remove_head
    **************************************************************/
    cout<< "<<Test list case 1_2>>: Start\n";
    new_list = create_list( new_list );
    temp = new_list;
    list_t *node2 = NULL;
    node1 = create_list( node1 );
    node2 = create_list( node2 );
    list_add_head( &new_list, node1 );
    EXPECT_EQ( temp->prev, new_list );
    EXPECT_EQ( temp->next, new_list );
    EXPECT_EQ( temp, new_list->prev );
    EXPECT_EQ( temp, new_list->next );
    list_add_tail( new_list, node2 );
    EXPECT_EQ( temp->next, node2 );
    EXPECT_EQ( temp, node2->prev );
    EXPECT_EQ( node2->next, new_list );
    EXPECT_EQ( new_list->prev, node2 );
    list_remove_tail(new_list);
    EXPECT_EQ( new_list->prev, temp );
    EXPECT_EQ( temp->next, new_list );
    new_list = list_remove_head( new_list );
    EXPECT_EQ( new_list->prev, new_list );
    EXPECT_EQ( new_list->next, new_list );
    free_list( new_list );
}

TEST( listremoventhnodecase, listremoventhnode_fun_test ){
    list_t *new_list = NULL, *node1 = NULL, *node2 = NULL, *node3 = NULL;
    new_list = create_list( new_list );
    node1 = create_list( node1 );
    node2 = create_list( node2 );
    list_add_head( &new_list, node1 );
    list_add_head( &new_list, node2 );
    list_remove_nth_node( &new_list, 0 );
    EXPECT_EQ( new_list, node1 );
    node3 = create_list( node3 );
    list_remove_nth_node( &new_list, 1 );
    list_add_head( &new_list, node3 );
    EXPECT_EQ( new_list, node3 );
    EXPECT_EQ( node1->prev, node3 );
}

/*
Test mul_stack_t
*/
TEST( TESTSTACK, stack_test ){
    cout<< "<<Test list_t>>: Start\n"; 
    mul_stack_t *stack = NULL;
    stack = create_stack( stack, 500 );
    EXPECT_NE( stack, nullptr );
    EXPECT_EQ( stack->capacity, 500 );
    EXPECT_EQ( stack->insert, list_add_tail );
    EXPECT_EQ( stack->remove, list_remove_tail );
    EXPECT_EQ( stack->count, 0 );
    EXPECT_EQ( stack->top, nullptr );
    EXPECT_EQ( stack->st.bit.configured, 1 );
    EXPECT_EQ( stack->st.bit.is_malloc, 1 );
    EXPECT_EQ( stack->st.bit.is_free, 0 );
    EXPECT_EQ( stack->st.bit.is_multithread, 1 );
    /*************************************************************
     *  Test stack 1_1: 
     *  Push: 1
     *  Pop: 1
    **************************************************************/
    cout<< "<<Test stack case 1_1>>: Start\n";
    push( stack, (void*)"I" );
    EXPECT_EQ( stack->count, 1 );
    EXPECT_NE( stack->top, nullptr );
    pop(stack);
    EXPECT_EQ( stack->count, 0 );
    /*************************************************************
     *  Test stack 1_2: 
     *  Push: 500
    **************************************************************/
    cout<< "<<Test stack case 1_2>>: Start\n";
    int i=0;
    while( i++ < 500){
       push( stack, (void*)i );
    }
    EXPECT_EQ( stack->count, 500 );
    EXPECT_NE( stack->top, nullptr );
}