#include "stack.h"

mul_stack_t* create_stack( mul_stack_t *stack,int capacity ){
    MUL_HODGEPODGE_ASSERT( !stack ,"Stack is Existed" );
    stack=MALLOC_MUL_T(stack)
    MUL_HODGEPODGE_ASSERT(stack , "Stack Memory allocated fail");

    stack->top = NULL;
    stack->insert = list_add_head;
    stack->remove = list_remove_head;
    stack->capacity = capacity;
    stack->count = 0;

    stack->stack_lock = (pthread_mutex_t *)malloc( sizeof(pthread_mutex_t) ) ;
    stack->stack_cond_cap = (pthread_cond_t *)malloc( sizeof(pthread_cond_t) );
    stack->stack_cond_empty = (pthread_cond_t *)malloc( sizeof(pthread_cond_t) );
    pthread_mutex_init(stack->stack_lock,NULL);
    pthread_condattr_t cattr;
    int ret = pthread_condattr_init(&cattr); 
    pthread_cond_init( stack->stack_cond_cap, &cattr );
    pthread_cond_init( stack->stack_cond_empty, &cattr );

    stack->st.w = 0;
    stack->st.w |= STRUCT_IS_ALLOCATED;
    stack->st.w |= STRUCT_IS_CREATED_BY_MALLOC;
    stack->st.w |= STRUCT_IS_MULTITHREAD;
    return stack;
}

stack_node_t* create_stack_node( void *value ){
    stack_node_t *stack_node = MALLOC_NODE_T(stack)
    list_t *temp = &stack_node->list;
    CONNECT_SELF( temp );
    stack_node->st.w = 0;
    stack_node->st.w |= STRUCT_IS_ALLOCATED;
    stack_node->st.w |= STRUCT_IS_CREATED_BY_MALLOC;
    stack_node->list.st.w = 0;
    stack_node->list.st.w |= STRUCT_IS_ALLOCATED;
    stack_node->value = value;
    return stack_node;
}

mul_stack_data_t* pack_stack_data( mul_stack_t *stack, void *value ){
    MUL_HODGEPODGE_ASSERT( IsAllocate( stack->st.w ), "Stack not allocated(pack_stack_data)" );
    mul_stack_data_t *stack_data = MALLOC_MUL_T(stack_data)
    MUL_HODGEPODGE_ASSERT(stack_data , "Stack Data Memory allocated fail");
    stack_data->stack = stack;
    stack_data->value = value;
    return stack_data;
}

void push( mul_stack_t *stack, void* value ){
    MUL_HODGEPODGE_ASSERT( IsAllocate( stack->st.w ), "Stack Not Allocated(push)" );
    MUL_HODGEPODGE_ASSERT( !IsFree( stack->st.w ), "Stack is already free(push)" );
    pthread_mutex_lock( stack->stack_lock );
    while( stack->count == stack->capacity ){
        puts("------Please Wait!! Stack is full !!------\n");
        pthread_cond_wait( stack->stack_cond_cap, stack->stack_lock );
    }
    if(!( stack->top )) {
        stack->top = create_stack_node( value );
        stack->top->st.w |= STRUCT_IS_ADDED;
    }
    else {
        stack_node_t *temp_stack_node = create_stack_node( value );
        temp_stack_node->st.w |= STRUCT_IS_ADDED;
        list_t *temp = &stack->top->list;
        stack->insert( &temp, &temp_stack_node->list );
        stack->top = temp_stack_node;
    }
    stack->count++;
    pthread_cond_signal( stack->stack_cond_empty );
    pthread_mutex_unlock( stack->stack_lock );
}


void* PUSH_INTF( void* stack_data_temp ){ 
    mul_stack_data_t *stack_data = (mul_stack_data_t *)stack_data_temp;
    mul_stack_t *stack = stack_data->stack;
    MUL_HODGEPODGE_ASSERT( IsAllocate( stack_data->stack->st.w ), "Stack not allocated.." );
    void *value = stack_data->value;
    push( stack, value );
    return NULL;
}

void pop( mul_stack_t *stack ){
    MUL_HODGEPODGE_ASSERT( IsAllocate( stack->st.w ), "Stack not allocated" );
    pthread_mutex_lock( stack->stack_lock );
    while( stack->count == 0 ){
        puts("------Please Wait!! Stack is Empty !!------\n");
        pthread_cond_wait( stack->stack_cond_empty, stack->stack_lock );
    }
    MUL_HODGEPODGE_ASSERT( IsAdd( stack->top->st.w ), "Stack not added can't remove.." );
    stack->count--;
    if( stack->count == 0 ) {
        free(stack->top);
        stack->top = NULL;
    }
    else{
        list_t* new_top_list = stack->remove( &stack->top->list );
        stack_node_t *temp = stack->top;
        stack->top = list_entry(new_top_list, stack_node_t, list);
        free(temp);
    }
    pthread_cond_signal( stack->stack_cond_cap );
    pthread_mutex_unlock( stack->stack_lock );
}

void free_stack( mul_stack_t **stack ){
    MUL_HODGEPODGE_ASSERT( IsAllocate( (*stack)->st.w ), "Stack not allocated" );
    if( !(*stack)->top ){
        free(*stack);
        *stack = NULL;
        return;
    }
    if( IsAllocate( (*stack)->st.w ) && !IsFree( (*stack)->st.w ) ){
        while( (*stack)->top != NULL){
            pop((*stack));
        }
        free((*stack)->stack_cond_cap);
        free((*stack)->stack_cond_empty);
        free((*stack)->stack_lock);
        free(*stack);
        *stack = NULL;
    }
}


