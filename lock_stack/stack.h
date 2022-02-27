#include "../list/list.h"
#include <pthread.h>
typedef struct stack{
    list_t *top;
    void (*insert_func)(list_t **,void *);
    void (*remove_func)(list_t **);
    int capacity;
    pthread_mutex_t *stack_lock;
}stack_t;
void create_stack(stack_t **,int);
void insert_stack(void*);
void remove_stack(stack_t *);