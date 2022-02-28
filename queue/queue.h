#include "../list/list.h"
#include <pthread.h>
#include <semaphore.h>
typedef struct queue {

    list_t *list;
    int counter;
    int capacity;
    void (*enqueue)(list_t**, void*);
    void (*dequeue)(list_t**);
    void (*printQueue)(list_t** );
    void (*freeQueue)(list_t **);
    pthread_mutex_t *queue_lock;
    sem_t *qremain, *qitem;
    
}queue_t;

typedef struct thread_param {
    queue_t *queue;
    void *val;
}threadpa_t;
void create_queue(queue_t **, int) ;
void enqueue(threadpa_t *);
void dequeue(queue_t **);
void print_queue(queue_t **);
void free_queue(queue_t **);