#include "stack.h"
/**
* @brief: create_stack()-Create and initialize stack
* @stack: A pointer to pointer to stack 
* @capacity: Capacity of stack
*/
void create_stack(stack_t **stack,int capacity){
    if((*stack)){
        printf("------Stack Already Exists------\n");
        return;
    }

    printf("Stack Creation\n");

    *stack=(stack_t *)malloc(sizeof(stack_t));
    (*stack)->top=NULL;
    (*stack)->insert_func=list_add_tail;
    (*stack)->remove_func=list_remove_tail;
    (*stack)->free_func=free_list;
    (*stack)->capacity=capacity;
    (*stack)->count=0;
    (*stack)->stack_lock=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    (*stack)->stack_cond_cap=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    (*stack)->stack_cond_empty=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    pthread_mutex_init((*stack)->stack_lock,NULL);

    pthread_condattr_t  cattr;
    int ret = pthread_condattr_init(&cattr); 
    pthread_cond_init((*stack)->stack_cond_cap,&cattr);
    pthread_cond_init((*stack)->stack_cond_empty,&cattr);
}

/**
* @brief: push()-Push node to stack
* @stack_param: Parameter to thread
*/
void push(threadpa_t *stack_param){
    stack_t *stack= stack_param->stack;


    if(!stack){
        printf("------Stack not exists------\n");
    }
    
    pthread_mutex_lock(stack->stack_lock);

    while(stack->count==stack->capacity){
        printf("------Please Wait!! Stack is full !!------\n");
        pthread_cond_wait(stack->stack_cond_cap,stack->stack_lock);
    }
    if(!(stack->top)) create_list(&(stack->top));
    else    stack->insert_func(stack->top, stack_param->node);
    stack->count++;
    pthread_cond_signal(stack->stack_cond_empty);
    pthread_mutex_unlock(stack->stack_lock);
}

/**
* @brief: pop()-Remove node from stack
* @stack: A pointer to pointer to stack 
*/
void pop(stack_t *stack){
    if(!stack){
        printf("------Stack not exists------\n");
    }
    pthread_mutex_lock(stack->stack_lock);
    while(stack->count==0){
        printf("------Please Wait!! Stack is Empty !!------\n");
        pthread_cond_wait(stack->stack_cond_empty,stack->stack_lock);
    }

    stack->remove_func(&stack->top);
    stack->count--;
    pthread_cond_signal(stack->stack_cond_cap);
    pthread_mutex_unlock(stack->stack_lock);
}

/**
* @brief: free_stack()-Free stack
* @stack: A pointer to stack 
*/
void free_stack(stack_t *stack){
    if(!stack) 
    {
        printf("Stack is Empty!\n");
        return ;
    }
    stack->free_func(&stack->top);
    stack->top = NULL;
    free(stack->stack_lock);
    stack->stack_lock = NULL;
    free(stack->stack_cond_cap);
    stack->stack_cond_cap = NULL;
    free(stack->stack_cond_empty);
    stack->stack_cond_empty = NULL;
    free(stack);
    stack = NULL;
}


