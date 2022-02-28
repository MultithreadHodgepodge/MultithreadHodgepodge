#include "queue.h"

/*  
* create a queue instance 
* @queue: return a queue instance
* @qun: queue quntity
*/

void create_queue(queue_t **queue, int qun) 
{
    (*queue) = (queue_t*)malloc(sizeof(queue_t));
    if (!*queue) {
        puts("Memory allocate fail");
        return ;
    }
    (*queue)->counter = 0;
    (*queue)->capacity = qun;
    (*queue)->enqueue = list_add_tail;
    (*queue)->dequeue = list_remove_head;
    (*queue)->printQueue = print_list;
    (*queue)->freeQueue = free_list;
    (*queue)->queue_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    (*queue)->qremain = (sem_t*)malloc(sizeof(sem_t));
    (*queue)->qitem = (sem_t*)malloc(sizeof(sem_t));

    sem_init((*queue)->qremain, 0, qun);
    sem_init((*queue)->qitem,  0, 0);

}

/*
* add a val into queue 
* @queue: return a queue after enqueue
* @val  : insert value
*/

void enqueue(threadpa_t *para)
{
    if (!para) {
        puts("parameter is empty\n");
        return ;
    }
    queue_t *q = para->queue;
    if (!q) {
        puts("queue is not exist\n");
        return ;
    }
    sem_wait(q->qremain);
    pthread_mutex_lock(q->queue_lock);
    q->enqueue(&q->list, para->val);
    q->counter++;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qitem);
}

/*
* remove first val in the queue
* @queue: return a queue after dequeue
*/
void dequeue(queue_t **queue)
{
    if (!*queue){
        puts("queue is not exist");
        return ;
    }
    queue_t *q = (*queue);
    sem_wait(q->qitem);
    pthread_mutex_lock(q->queue_lock);
    (*queue)->dequeue(&(*queue)->list);
    (*queue)->counter--;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qremain);
}


/*
* show contents of queue
* @queue: return a queue after print_queue
*/
void print_queue(queue_t **queue)
{
    if (!*queue) {
        puts("queue is empty\n");
        return ;
    }
    pthread_mutex_lock((*queue)->queue_lock);
    if (!*queue){
        puts("Queue is empty\n");
        return ;
    }
    (*queue)->printQueue(&(*queue)->list);
    pthread_mutex_unlock((*queue)->queue_lock);
}

/*
* free list of queue
* @queue: return queue after free_queue
*/
void free_queue(queue_t **queue) 
{
    if (!*queue) {
        puts("queue is empty\n");
        return ;
    }
    pthread_mutex_lock((*queue)->queue_lock);
    if (!*queue){
        puts("It's already null");
        return;
    }

    (*queue)->freeQueue(&(*queue)->list);
    pthread_mutex_unlock((*queue)->queue_lock);
}