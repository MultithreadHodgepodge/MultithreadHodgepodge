#include "../list/list.h"
#include "../Observer/observer.h"
#include <pthread.h>
#include<stdbool.h>
typedef struct __stack{
    list_t *top;
    observer_t *observer;
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

void create_stack(stack_t **,int);
void push(struct thread_param*);
void pop(stack_t *);
void print_stack(stack_t *);
void free_stack(stack_t *);
bool isEmpty(stack_t *);

