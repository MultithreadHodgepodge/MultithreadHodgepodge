#include "stack.h"
/**
* @brief: create_stack()-Create and initialize stack
* @stack: A pointer to stack 
* @capacity: Capacity of stack
*/
mul_stack_t* create_stack(mul_stack_t *stack,int capacity){
    MUL_HODGEPODGE_ASSERT(!stack , "Stack is Existed");
    printf("Stack Creation\n");
    stack=(mul_stack_t *)malloc(sizeof(mul_stack_t));
    MUL_HODGEPODGE_ASSERT(stack , "Stack Memory allocated fail");
    stack->top=NULL;
    stack->insert=list_add_tail;
    stack->remove=list_remove_tail;
    stack->capacity=capacity;
    stack->count=0;
    stack->stack_lock=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    stack->stack_cond_cap=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    stack->stack_cond_empty=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(stack->stack_lock,NULL);
    pthread_condattr_t  cattr;
    int ret = pthread_condattr_init(&cattr); 
    pthread_cond_init(stack->stack_cond_cap,&cattr);
    pthread_cond_init(stack->stack_cond_empty,&cattr);
    stack->st.w=0;
    stack->st.bit.configured=1;
    stack->st.bit.is_malloc=1;
    stack->st.bit.is_free=0;
    stack->st.bit.is_multithread=1;
    return stack;
}

/**
* @brief: create_stack_node()-Create and initialize stack node
* @value: Value to be packed in stack node
*/
stack_node_t* create_stack_node(void *value){
    stack_node_t *stack_node=(stack_node_t*)malloc(sizeof(stack_node_t));
    list_t *temp=&stack_node->list;
    CONNECT_SELF(temp);
    stack_node->st.w=0;
    stack_node->st.bit.configured=1;
    stack_node->st.bit.is_malloc=1;
    stack_node->list.st.w=0;
    stack_node->list.st.bit.configured=1;
    stack_node->list.st.bit.is_malloc=0;
    stack_node->value=value;
    return stack_node;
}

/**
* @brief: pack_stack_data()-Pack stack and stack_node into stack_data
* @stack: A pointer to stack 
* @stack_node: Pointer to stack_node
*/
mul_stack_data_t* pack_stack_data(mul_stack_t *stack, void *value){
    MUL_HODGEPODGE_ASSERT(stack->st.w & STRUCT_IS_ALLOCATED, "Stack not allocated");
    mul_stack_data_t *stack_data=(mul_stack_data_t*) malloc(sizeof(mul_stack_data_t));
    stack_data->stack=stack;
    stack_data->value=value;
    return stack_data;
}

/**
* @brief: push()-Push node to stack
* @stack_param: Parameter to thread
*/
void push(mul_stack_data_t *stack_data){
    mul_stack_t *stack=stack_data->stack;
    void *value=stack_data->value;
    MUL_HODGEPODGE_ASSERT(stack->st.w & STRUCT_IS_ALLOCATED, "Stack not allocated");
    pthread_mutex_lock(stack->stack_lock);
    while(stack->count==stack->capacity){
        printf("------Please Wait!! Stack is full !!------\n");
        pthread_cond_wait(stack->stack_cond_cap,stack->stack_lock);
    }
    if(!(stack->top)) {
            stack->top=create_stack_node(value);
    }
    else {
        stack_node_t *temp_stack_node=create_stack_node(value);
        stack->insert(&stack->top->list, &temp_stack_node->list);
    }
    stack->count++;
    pthread_cond_signal(stack->stack_cond_empty);
    pthread_mutex_unlock(stack->stack_lock);
}

/**
* @brief: pop()-Remove node from stack
* @stack: A pointer to pointer to stack 
*/
void pop(mul_stack_t *stack){
    MUL_HODGEPODGE_ASSERT(stack , "Stack is Empty");
    pthread_mutex_lock(stack->stack_lock);
    while(stack->count==0){
        printf("------Please Wait!! Stack is Empty !!------\n");
        pthread_cond_wait(stack->stack_cond_empty,stack->stack_lock);
    }
    stack->remove(&stack->top->list);
    stack->count--;
    if(stack->count==0) {
        stack->top->st.w=0;
        stack->top->st.bit.is_free=1;
        if(stack->top->st.w & STRUCT_IS_CREATED_BY_MALLOC) free(stack->top);
        stack->top=NULL;
    }
    pthread_cond_signal(stack->stack_cond_cap);
    pthread_mutex_unlock(stack->stack_lock);
}

/**
* @brief: free_stack()-Free stack
* @stack: A pointer to stack 
*/
void free_stack(mul_stack_t **stack){
    MUL_HODGEPODGE_ASSERT(*stack , "Stack is Empty");
    if((*stack)->top->st.bit.configured)
        free_list(&((*stack)->top)->list);
    (*stack)->top = NULL;
    free((*stack)->stack_lock);
    (*stack)->stack_lock = NULL;
    free((*stack)->stack_cond_cap);
    (*stack)->stack_cond_cap = NULL;
    free((*stack)->stack_cond_empty);
    (*stack)->stack_cond_empty = NULL;
    free(*stack);
    *stack = NULL;
}


