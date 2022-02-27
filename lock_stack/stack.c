#include<stdio.h>
#include "stack.h"

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
    (*stack)->capacity=capacity;
    (*stack)->stack_lock=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init((*stack)->stack_lock,NULL);
}
void insert_stack(struct thread_param *stack_param){
    stack_t *stack=stack_param->stack;
    void *value=stack_param->value;
    if(!stack){
        printf("------Stack not exists------\n");
    }

    stack->insert_func(&(stack->top),value);

}
void remove_staack(stack_t *stack){
    if(!stack){
        printf("------Stack not exists------\n");
    }
    stack->remove_func(&stack->top);
}