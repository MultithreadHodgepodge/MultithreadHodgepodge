#include "queue.h"

/**  
* @brief: reate_queue()-create a queue instance 
* @queue: return a queue instance
* @qun: queue quntity
*/
void create_queue(mul_queue_t **queue, int qun) 
{
    MUL_HODGEPODGE_ASSERT(!(*queue) , "Stack is Existed");
    (*queue) = (mul_queue_t*)malloc(sizeof(mul_queue_t));
    
    MUL_HODGEPODGE_ASSERT((*queue) , "Stack Memory allocated fail");
    (*queue)->list = NULL;
    (*queue)->counter = 0;
    (*queue)->capacity = qun;
    (*queue)->enqueue = list_add_tail;
    (*queue)->dequeue = list_remove_head;
    (*queue)->freeQueue = free_list;
    (*queue)->queue_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    (*queue)->qremain = (sem_t*)malloc(sizeof(sem_t));
    (*queue)->qitem = (sem_t*)malloc(sizeof(sem_t));

    sem_init((*queue)->qremain, 0, qun);
    sem_init((*queue)->qitem,  0, 0);
    pthread_mutex_init((*queue)->queue_lock, NULL);
}

/**
* @brief: enqueue()-add a node into queue 
* @para: Parameter send to thread 
*/
void enqueue(threadpa_t *para)
{
    if (!para) {
        puts("parameter is empty\n");
        return ;
    }
    mul_queue_t *q = para->mul_queue;
    if (!q) {
        puts("queue is not exist\n");
        return ;
    }
    sem_wait(q->qremain);
    pthread_mutex_lock(q->queue_lock);
    if(!(q->list)) create_list(&(q->list));
    else    q->enqueue(q->list, para->node);
    q->counter++;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qitem);
}

/**
* @brief: dequeue()-remove first node from the queue
* @queue: pointer to pointer to queue
*/
void dequeue(mul_queue_t **queue)
{
    if (!*queue){
        puts("queue is not exist");
        return ;
    }
    mul_queue_t *q = (*queue);
    sem_wait(q->qitem);
    pthread_mutex_lock(q->queue_lock);
    (*queue)->dequeue(&(*queue)->list);
    (*queue)->counter--;
    pthread_mutex_unlock(q->queue_lock);
    sem_post(q->qremain);
}


/**
* @brief: free_queue()-free queue
* @queue: pointer to pointer to queue
*/
void free_queue(mul_queue_t **queue) 
{
    MUL_HODGEPODGE_ASSERT(!(*queue) , "Queue is Empty");
    (*queue)->freeQueue(&(*queue)->list);
    free((*queue)->qremain);
    (*queue)->qremain = NULL;
    free((*queue)->qitem);
    (*queue)->qitem = NULL;
    free((*queue)->queue_lock);
    (*queue)->queue_lock = NULL;
    free(*queue);
    (*queue) = NULL;
}