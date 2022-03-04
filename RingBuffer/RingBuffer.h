#include "../list/list.h"
#include <pthread.h>

typedef struct Ringbuffer {

    int counter;
    list_t *front, *tail;
    pthread_mutex_t *lock;
    pthread_cond_t *full, *empty;

}Ringbuffer_t;

typedef struct thread_param {
    Ringbuffer_t *rb;
    void *val;
}threadpa_t;

void createRB(Ringbuffer_t **, int);
void enqueue(threadpa_t *);
void dequeue(threadpa_t *);
void printRB(Ringbuffer_t *);