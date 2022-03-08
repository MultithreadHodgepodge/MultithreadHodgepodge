#include "../list/list.h"
typedef struct __observer{
    pthread_t thread_list[];
}observer_t;
struct thread_param{
    stack_t *stack;
    void *value;
};
void observer_constructor(observer_t **);
pthread_t* create_thread(observer *,void (*thread_func)(struct thread_param *),struct thread_param *);
   