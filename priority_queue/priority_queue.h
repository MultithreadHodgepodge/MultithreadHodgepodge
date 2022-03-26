#include "queue.h"
typedef struct __priority_queue {

    queue_t *queue;
    
}priority_queue_t;
DECLARE_THREAD(priority_queue)
void create_priority_queue(priority_queue_t **, int) ;
void enqueue(threadpa_t *);
void dequeue(priority_queue_t **);
void print_queue(priority_queue_t **);
void free_queue(priority_queue_t **);