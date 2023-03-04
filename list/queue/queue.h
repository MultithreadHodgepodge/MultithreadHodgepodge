#include "../list.h"
#include <pthread.h>
#include <semaphore.h>
#include "../../common/test_macro.h"
#include "../../common/mul_hodgepodge_assert.h"
typedef struct queue {
    list_t *list;
    int counter;
    int capacity;
    void (*enqueue)(list_t*, list_t *);
    void (*dequeue)(list_t**);
    void (*freeQueue)(list_t **);
    pthread_mutex_t *queue_lock;
    sem_t *qremain, *qitem;
}mul_queue_t;

DECLARE_THREAD(mul_queue,list_t*)
mul_queue_t* create_queue(mul_queue_t *, int) ;
void enqueue(threadpa_t *);
void dequeue(mul_queue_t **);
void free_queue(mul_queue_t *);