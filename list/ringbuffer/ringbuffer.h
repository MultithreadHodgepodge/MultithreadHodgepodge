#include "../list.h"
#include "../../common/test_macro.h"
#include <pthread.h>

typedef struct Ringbuffer {

    int counter;
    list_t *front, *tail;
    pthread_mutex_t *lock;
    pthread_cond_t *full, *empty;

}Ringbuffer_t;

DECLARE_THREAD(Ringbuffer)

void createRingbuffer(Ringbuffer_t **, int);
void enqueue(threadpa_t *);
void dequeue(threadpa_t *);
void freeRingbuffer(Ringbuffer_t **);