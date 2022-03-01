#include "../list/list.h"
#include <pthread.h>
#include<stdbool.h>
typedef struct stack{
    list_t *top;
    void (*insert_func)(list_t **,void *);
    void (*remove_func)(list_t **);
    void (*print_func)(list_t **);
    void (*free_func)(list_t **);
    int capacity;
    int count;
    pthread_mutex_t *stack_lock;
    pthread_cond_t *stack_cond_cap;
    pthread_cond_t *stack_cond_empty;
}stack_t;
struct thread_param{
    stack_t *stack;
    void *value;
};
void create_stack(stack_t **,int);
void push(struct thread_param*);
void pop(stack_t *);
void print_stack(stack_t *);
void free_stack(stack_t *);
bool isEmpty(stack_t *);
