#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>
#include<stdbool.h>
#include "../../common/mul_hodgepodge_assert.h"

typedef struct stack{
    list_t *top;
    void (*insert)(list_t *,list_t *);
    void (*remove)(list_t **);
    int capacity;
    int count;
    pthread_mutex_t *stack_lock;
    pthread_cond_t *stack_cond_cap;
    pthread_cond_t *stack_cond_empty;
}mul_stack_t;

#if defined(MUL_HOD_UT) 
    extern mul_stack_t* create_stack(mul_stack_t *,int) ;
    extern void push(mul_stack_t *);
    extern void pop(mul_stack_t *);
    extern void free_stack(mul_stack_t *);
    extern bool isEmpty(mul_stack_t *);
#else
    mul_stack_t* create_stack(mul_stack_t *,int) ;
    void push(mul_stack_t *);
    void pop(mul_stack_t *);
    void free_stack(mul_stack_t *);
    bool isEmpty(mul_stack_t *);
#endif