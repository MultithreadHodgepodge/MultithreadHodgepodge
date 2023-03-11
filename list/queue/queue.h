#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>
#include <semaphore.h>
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

#if defined(MUL_HOD_UT) 
    extern mul_queue_t* create_queue(mul_queue_t *, int) ;
    extern void enqueue(mul_queue_t*);
    extern void dequeue(mul_queue_t **);
    extern void free_queue(mul_queue_t **);
#else
    mul_queue_t* create_queue(mul_queue_t *, int) ;
    void enqueue(mul_queue_t*);
    void dequeue(mul_queue_t **);
    void free_queue(mul_queue_t **);
#endif