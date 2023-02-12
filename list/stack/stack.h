#include "../list.h"
#include <pthread.h>
#include<stdbool.h>
#include "../../common/test_macro.h"
#include"../../common/threadpa_macro.h"
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

DECLARE_THREAD(mul_stack,list_t*)

void create_stack(mul_stack_t **,int) ;
void push(threadpa_t *);
void pop(mul_stack_t *);
void free_stack(mul_stack_t *);
bool isEmpty(mul_stack_t *);

