#include "../list.h"
#include <pthread.h>

#include<stdbool.h>
#include "../../common/test_macro.h"
typedef struct __stack{
    list_t *top;
    void (*insert_func)(list_t *,list_t *);
    void (*remove_func)(list_t **);
    void (*free_func)(list_t **);
    int capacity;
    int count;
    pthread_mutex_t *stack_lock;
    pthread_cond_t *stack_cond_cap;
    pthread_cond_t *stack_cond_empty;
}stack_t;

DECLARE_THREAD(stack)

void create_stack(stack_t **,int) ;
void push(threadpa_t *);
void pop(stack_t *);
void free_stack(stack_t *);
bool isEmpty(stack_t *);

