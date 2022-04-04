
#include "../list/list.h"
#include "../common/test_macro.h"
#include <pthread.h>
#include <semaphore.h>
typedef struct __priority_queue {
    list_t *list;
    int counter;
    int capacity;
    void (*enqueue)(list_t**, void*,int(*compare)(const void *, const void*));
    void (*dequeue)(list_t**);
    void (*printQueue)(list_t** );
    void (*freeQueue)(list_t **);
    pthread_mutex_t *queue_lock;
    sem_t *qremain, *qitem;
    
}priority_queue_t;
DECLARE_THREAD(priority_queue)
void create_priority_queue(priority_queue_t **, int) ;
void enqueue(threadpa_t *);
void dequeue(priority_queue_t **);
void print_queue(priority_queue_t **);
void free_queue(priority_queue_t **);