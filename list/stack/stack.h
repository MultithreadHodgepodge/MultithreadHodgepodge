#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>
#include<stdbool.h>
#include<sys/time.h>
#include "../../common/mul_hodgepodge_assert.h"

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
    void (*remove)(list_t **);
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
    extern mul_stack_data_t* pack_stack_data(mul_stack_t *, void *value);
    extern void push(mul_stack_data_t *);
    extern void pop(mul_stack_t *);
    extern void free_stack(mul_stack_t **);
#else
    mul_stack_t* create_stack(mul_stack_t *,int) ;
    stack_node_t* create_stack_node(void*);
    mul_stack_data_t* pack_stack_data(mul_stack_t *, void *value);
    void push(mul_stack_data_t *);
    void pop(mul_stack_t *);
    void free_stack(mul_stack_t **);
#endif