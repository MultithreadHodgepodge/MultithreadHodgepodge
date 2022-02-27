#include "../list/list.h"
#include <pthread.h>

typedef struct stack{
    list_t *top;
    void (*insert_func)(list_t **,void *);
    void (*remove_func)(list_t **);
    void (*print_func)(list_t **);
    int capacity;
    pthread_mutex_t *stack_lock;
}stack_t;
struct thread_param{
    stack_t *stack;
    void *value;
};
void create_stack(stack_t **,int);
void insert_stack(struct thread_param*);
<<<<<<< HEAD
void remove_stack(stack_t *);
=======
void remove_stack(stack_t *);
void print_stack(stack_t *);
>>>>>>> c17cbf07e9570cbfe755cc0cefed2e8c3dfa00d5
