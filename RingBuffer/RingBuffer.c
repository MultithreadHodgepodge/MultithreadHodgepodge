#include "RingBuffer.h"
#include "../list/list.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * @rb: Return a ringbuffer object if allocate success
 * @qun: size of buffer size
 */
void createRB(Ringbuffer_t **rb, int qun)
{
    /*  Check if ring buffer is exist */
    if (*rb) {
        puts("RingBuffer already exist!\n");
        return ;
    }
    
    /* Check if ring buffer can not be allocated */
    *rb = (Ringbuffer_t *)malloc(sizeof(Ringbuffer_t));
    if (!*rb) {
        puts("RingBuffer memory allocate failed");
        return ;
    }

    /* Check if list can not be allcated */
    (*rb)->counter = 0;
    create_list(&(*rb)->front, -1);
    if (!(*rb)->front) {
        puts("list_allocate failed\n");
        free(*rb);
        return ;
    }

    /* Allcate enough size of ring buffer */
    int i;
    for (i = 0;i < qun - 1;++i) {
        if (list_add_tail(&(*rb)->front, -1)) {
            printf("%d st list allocate failed\n", i);
            free_list(&(*rb)->front);
            return ;
        } 
    }

    /* Reset pointer */
    (*rb)->tail = (*rb)->front;

    /* Allocate lock */
    (*rb)->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!(*rb)->lock) {
        puts("Lock allocate failed");
        free_list(&(*rb)->front);
        free_list(*rb);
        return ;
    }

    /* set mutex type */
    pthread_mutex_init((*rb)->lock, NULL);
    //pthread_mutexattr_settype((*rb)->lock, PTHREAD_MUTEX_ERRORCHECK);

    /* Allocate condition variable full */
    (*rb)->full = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    if (!(*rb)->full) {
        puts("condition variable full allocate failed\n");
        free((*rb)->lock);
        free_list(&(*rb)->front);
        free(*rb);
    }

    /* Allocate condition variable empty */
    (*rb)->empty = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    if(!(*rb)->empty) {
        puts("condition variable empty allocate failed\n");
        free((*rb)->lock);
        free((*rb)->lock);
        free_list(&(*rb)->front);
        free(*rb);
        return ;
    }
    pthread_condattr_t cattr;
    int ret = pthread_condattr_init(&cattr);
    pthread_cond_init((*rb)->full, &cattr);
    pthread_cond_init((*rb)->empty, &cattr);

}

/*
 *@t: thread parameter
 */
void enqueue(threadpa_t *t)
{
    /* Check if t is exist */
    if (!t) {
        puts("Enqueue: No parameter in here\n");
        return ;
    }

    /* Check if ring buffer is exist */
    if (!t->rb) {
        puts("Enqueue: No Ringbuffer object\n");
        return ;
    }

    Ringbuffer_t *rb = t->rb;
    /* Concurrency */
    pthread_mutex_lock(t->rb->lock);
    /* If RingBuffer is full, wait here for signal */
    while (rb->front == rb->tail && rb->tail->value != -1) {
        puts("Enqueue: RingBuffer is full!\n");
        pthread_cond_wait(t->rb->full, t->rb->lock);    
    }

    rb->front->value = t->val;
    printf("enqueue %d into RingBuffer\n", t->val);
    rb->front = rb->front->next;
    /* Wake up empty for dequeue */
    pthread_cond_signal(t->rb->empty);
    /* Unlock */
    pthread_mutex_unlock(t->rb->lock);
}

/*
 *@t: thread parameter
 */
void dequeue(threadpa_t *t)
{
    if (!t) {
        puts("Dequeue: No parameter in here\n");
        return ;
    }

    if (!t->rb) {
        puts("Dequeue: No Ringbuffer object\n");
        return ;
    }

    Ringbuffer_t *rb = t->rb;
    pthread_mutex_lock(t->rb->lock);

    /* Check buffer is empty or not */
    while (rb->front == rb->tail && rb->tail->value == -1) {
        puts("dequeue: RingBuffer is empty\n");
        pthread_cond_wait(t->rb->empty, t->rb->lock);
    } 
    int val = rb->tail->value;
    rb->tail->value = -1;
    printf("%d is dequeue\n", val);
    rb->tail = rb->tail->next;
    pthread_cond_signal(t->rb->full);
    pthread_mutex_unlock(t->rb->lock);
}

/*
 *@t: thread parameter
 */
void printRB(Ringbuffer_t *rb)
{
    if (!rb) {
        puts("RingBuffer is not exist\n");
        return ;
    }

    if (!rb->front) {
        puts("RingBuffer's list is mot exist\n");
        return ;
    }

    pthread_mutex_lock(rb->lock);
    print_list(&rb->front);
    pthread_mutex_unlock(rb->lock);
}