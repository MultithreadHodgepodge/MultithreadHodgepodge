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
    void (*enqueue)( list_t*, list_t * );
    list_t* (*dequeue)( list_t* );
    void (*freeQueue)( list_t * );
    pthread_mutex_t *queue_lock;
    sem_t *qremain, *qitem;
    state st;
}mul_queue_t;

typedef struct __queue_data{
    void *value;
    mul_queue_t *queue;
}mul_queue_data_t;

#if defined(MUL_HOD_UT) 
    extern mul_queue_t* create_queue( mul_queue_t *, int );
    extern queue_node_t* create_queue_node( void* );
    extern mul_queue_data_t* pack_queue_data( mul_queue_t *, void * );
    extern void enqueue( mul_queue_data_t* );
    extern void dequeue( mul_queue_t ** );
    extern void free_queue( mul_queue_t ** );
#else
/**  
* @brief: reate_queue()-create a queue instance 
* @queue: return a queue instance
* @qun: queue quntity
* @return: mul_queue_t be created
*/
mul_queue_t* create_queue( mul_queue_t *, int ) ;
/**
* @brief: create_queue_node()-Create and initialize queue node
* @value: Value to be packed in queue node
* @return: queue_node_t be created
*/
queue_node_t* create_queue_node( void* );
/**
* @brief: pack_queue_data()-Pack queue and value into queue_data, the queue_data will be used as multithread function input.
* @queue: A pointer to queue
* @stack_node: Pointer to value
* @return: mul_queue_data_t be created
*/
mul_queue_data_t* pack_queue_data( mul_queue_t *, void *value );
/**
* @brief: enqueue()-Add a node into queue 
* @para: Parameter send to thread 
*/
void enqueue( mul_queue_data_t* );
/**
* @brief: dequeue()-Remove first node from the queue
* @queue: pointer to pointer to mul_queue_t
*/
void dequeue( mul_queue_t ** );
/**
* @brief: free_queue()-free queue
* @queue: pointer to pointer to mul_queue_t
*/
void free_queue( mul_queue_t ** );
#endif