#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>
#include<stdbool.h>
#include<sys/time.h>
#include "../../common/mul_hodgepodge_assert.h"
#include "../../common/mul_hod_malloc.h"
#ifndef STACK_NODE_H__


typedef struct __stack_node{
    void *value;
    list_t list;
    state st;
}stack_node_t;
#endif


typedef struct stack{
    stack_node_t *top;
    void (*insert)(list_t *,list_t *);
    void (*remove)(list_t *);
    int capacity;
    int count;
    pthread_mutex_t *stack_lock;
    pthread_cond_t *stack_cond_cap;
    pthread_cond_t *stack_cond_empty;
    state st;
}mul_stack_t;

typedef struct __stack_data{
    void *value;
    mul_stack_t *stack;
}mul_stack_data_t;

#if defined(MUL_HOD_UT) 
    extern mul_stack_t* create_stack(mul_stack_t *,int) ;
    extern stack_node_t* create_stack_node(void*);
    extern mul_stack_data_t* pack_stack_data(mul_stack_t *, void *value);
    extern void push(mul_stack_data_t *);
    extern void pop(mul_stack_t *);
    extern void free_stack(mul_stack_t **);
#else
/**
* @brief: create_stack()-Create and initialize stack
* @stack: A pointer to stack 
* @capacity: Capacity of stack
* @return: mul_stack_t be created
*/
mul_stack_t* create_stack(mul_stack_t *,int);
/**
* @brief: create_stack_node()-Create and initialize stack node
* @value: Value to be packed in stack node
* @retuen: stack_node_t be created
*/
stack_node_t* create_stack_node(void*);
/**
* @brief: pack_stack_data()-Pack stack and value into stack_data
* @stack: A pointer to stack 
* @value: Pointer to value
* @return: mul_stack_data_t be created
*/
mul_stack_data_t* pack_stack_data(mul_stack_t *, void *value);
/**
* @brief: push()-Push node to stack
* @stack_param: Parameter to thread
*/
void push(mul_stack_data_t *);
/**
* @brief: pop()-Remove node from stack
* @stack: A pointer to mul_stack_t 
*/
void pop(mul_stack_t *);
/**
* @brief: free_stack()-Free stack
* @stack: A pointer to pointer to stack 
*/
void free_stack(mul_stack_t **);
#endif