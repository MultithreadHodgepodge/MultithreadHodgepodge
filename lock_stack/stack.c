#include<stdio.h>
#include "stack.h"
/*
* Create and initialize stack
* @stack: A pointer to pointer which point to stack 
* @capacity: Capacity of stack
*/
void create_stack(stack_t **stack,int capacity){
    if((*stack)){
        printf("------Stack Already Exists------\n");
        return;
    }

    printf("Stack Creation\n");

    *stack=(stack_t *)malloc(sizeof(stack_t));
    //list_t *top=(list_t *)malloc(sizeof(list_t));
    (*stack)->top=NULL;
    (*stack)->insert_func=&list_add_tail;
    (*stack)->remove_func=&list_remove_tail;
    (*stack)->print_func=&print_list;
    (*stack)->capacity=capacity;
    (*stack)->stack_lock=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init((*stack)->stack_lock,NULL);
}

/*
* Add node to stack
* @stack_param: A thread_param structure contains struct and node value
*/
void insert_stack(struct thread_param *stack_param){
    stack_t *stack= stack_param->stack;
    void *value=stack_param->value;
    if(!stack){
        printf("------Stack not exists------\n");
    }
    pthread_mutex_lock(stack->stack_lock);
    stack->insert_func(&(stack->top),value);
    pthread_mutex_unlock(stack->stack_lock);
}

/*
* Remove node from stack
* @stack: A pointer to pointer which point to stack 
*/
void remove_stack(stack_t *stack){
    if(!stack){
        printf("------Stack not exists------\n");
    }
    pthread_mutex_lock(stack->stack_lock);
    stack->remove_func(&stack->top);
    pthread_mutex_unlock(stack->stack_lock);
}

/*
* Print node in stack
* @stack: A pointer to pointer which point to stack 
*/
void print_stack(stack_t *stack){
    stack->print_func(&stack->top);
}