#include "priority_queue.h"
void create_priority_queue(priority_queue_t **queue, int qun) {
    (*queue)=(priority_queue_t*)malloc(sizeof(priority_queue_t));
    if (!*queue) {
        puts("Memory allocate fail");
        return ;
    }
    (*queue)->list = NULL;
    (*queue)->counter = 0;
    (*queue)->capacity = qun;
    (*queue)->enqueue = list_add_before_larger_smaller;
    (*queue)->dequeue = list_remove_head;
    (*queue)->printQueue = print_list;
    (*queue)->freeQueue = free_list;
    (*queue)->queue_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    (*queue)->qremain = (sem_t*)malloc(sizeof(sem_t));
    (*queue)->qitem = (sem_t*)malloc(sizeof(sem_t));

    sem_init((*queue)->qremain, 0, qun);
    sem_init((*queue)->qitem,  0, 0);
    pthread_mutex_init((*queue)->queue_lock, NULL);
}
void enqueue(threadpa_t *para){
    if (!para) {
        puts("parameter is empty\n");
        return ;
    }
    priority_queue_t *q = para->priority_queue;
    if (!q) {
        puts("priority queue is not exist\n");
        return ;
    }
    sem_wait(q->qremain);
    pthread_mutex_lock(q->queue_lock);
    q->enqueue(&q->list, para->value,smaller);
    q->counter++;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qitem);
    
}

void dequeue(priority_queue_t **queue){
    if (!*queue){
        puts("queue is not exist");
        return ;
    }
    priority_queue_t *q = (*queue);
    sem_wait(q->qitem);
    pthread_mutex_lock(q->queue_lock);
    (*queue)->dequeue(&(*queue)->list);
    (*queue)->counter--;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qremain);
}



void print_queue(priority_queue_t **queue){
    if (!*queue) {
        puts("queue is empty\n");
        return ;
    }
    pthread_mutex_lock((*queue)->queue_lock);  
    puts("queue list: ");
    (*queue)->printQueue(&(*queue)->list);
    pthread_mutex_unlock((*queue)->queue_lock);
}

void free_queue(priority_queue_t **queue){
    if (!*queue) {
        puts("queue is empty\n");
        return ;
    }
    (*queue)->freeQueue(&(*queue)->list);
    free((*queue)->qremain);
    free((*queue)->qitem);
    free((*queue)->queue_lock);
    free(*queue);
}