#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>
#include <semaphore.h>
#include "../../common/mul_hodgepodge_assert.h"
#include "../../common/mul_hod_malloc.h"

#ifndef QUEUE_NODE_H__
typedef struct __queue_node{
    void *value;
    list_t list;
    state st;
}queue_node_t;
#endif

typedef struct queue {
    queue_node_t *head;
    int counter;
    int capacity;
    void (*enqueue)(list_t*, list_t *);
    list_t* (*dequeue)(list_t*);
    void (*freeQueue)(list_t *);
    pthread_mutex_t *queue_lock;
    sem_t *qremain, *qitem;
    state st;
}mul_queue_t;

typedef struct __queue_data{
    void *value;
    mul_queue_t *queue;
}mul_queue_data_t;

#if defined(MUL_HOD_UT) 
    extern mul_queue_t* create_queue(mul_queue_t *, int) ;
    extern queue_node_t* create_queue_node(void*);
    extern mul_queue_data_t* pack_queue_data(mul_queue_t *, void *value);
    extern void enqueue(mul_queue_data_t*);
    extern void dequeue(mul_queue_t **);
    extern void free_queue(mul_queue_t **);
#else
    mul_queue_t* create_queue(mul_queue_t *, int) ;
    queue_node_t* create_queue_node(void*);
    mul_queue_data_t* pack_queue_data(mul_queue_t *, void *value);
    void enqueue(mul_queue_data_t*);
    void dequeue(mul_queue_t **);
    void free_queue(mul_queue_t **);
#endif