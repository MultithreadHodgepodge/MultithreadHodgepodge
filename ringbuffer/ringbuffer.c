#include "ringbuffer.h"
#include "../list/list.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * @Ringbuffer: Return a ringbuffer object if allocate success
 * @qun: size of buffer size
 */
void createRingbuffer(Ringbuffer_t **Ringbuffer, int qun)
{
    /*  Check if ring buffer is exist */
    if (*Ringbuffer) {
        puts("RingBuffer already exist!\n");
        return ;
    }
    
    /* Check if ring buffer can not be allocated */
    *Ringbuffer = (Ringbuffer_t *)malloc(sizeof(Ringbuffer_t));
    if (!*Ringbuffer) {
        puts("RingBuffer memory allocate failed");
        return ;
    }

    /* Check if list can not be allcated */
    (*Ringbuffer)->counter = 0;
    create_list(&(*Ringbuffer)->front, -1);
    if (!(*Ringbuffer)->front) {
        puts("list_allocate failed\n");
        free(*Ringbuffer);
        return ;
    }

    /* Allcate enough size of ring buffer */
    int i;
    for (i = 0;i < qun - 1;++i) {
        if (list_add_tail(&(*Ringbuffer)->front, -1)) {
            printf("%d st list allocate failed\n", i);
            free_list(&(*Ringbuffer)->front);
            return ;
        } 
    }

    /* Reset pointer */
    (*Ringbuffer)->tail = (*Ringbuffer)->front;

    /* Allocate lock */
    (*Ringbuffer)->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!(*Ringbuffer)->lock) {
        puts("Lock allocate failed");
        free_list(&(*Ringbuffer)->front);
        free_list(*Ringbuffer);
        return ;
    }

    /* set mutex type */
    pthread_mutex_init((*Ringbuffer)->lock, NULL);
    //pthread_mutexattr_settype((*Ringbuffer)->lock, PTHREAD_MUTEX_ERRORCHECK);

    /* Allocate condition variable full */
    (*Ringbuffer)->full = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    if (!(*Ringbuffer)->full) {
        puts("condition variable full allocate failed\n");
        free((*Ringbuffer)->lock);
        free_list(&(*Ringbuffer)->front);
        free(*Ringbuffer);
    }

    /* Allocate condition variable empty */
    (*Ringbuffer)->empty = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    if(!(*Ringbuffer)->empty) {
        puts("condition variable empty allocate failed\n");
        free((*Ringbuffer)->lock);
        free((*Ringbuffer)->lock);
        free_list(&(*Ringbuffer)->front);
        free(*Ringbuffer);
        return ;
    }
    pthread_condattr_t cattr;
    int ret = pthread_condattr_init(&cattr);
    pthread_cond_init((*Ringbuffer)->full, &cattr);
    pthread_cond_init((*Ringbuffer)->empty, &cattr);

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
    if (!t->Ringbuffer) {
        puts("Enqueue: No Ringbuffer object\n");
        return ;
    }

    Ringbuffer_t *Ringbuffer = t->Ringbuffer;
    /* Concurrency */
    pthread_mutex_lock(t->Ringbuffer->lock);
    /* If RingBuffer is full, wait here for signal */
    while (Ringbuffer->front == Ringbuffer->tail && Ringbuffer->tail->value != -1) {
        puts("Enqueue: RingBuffer is full!\n");
        pthread_cond_wait(t->Ringbuffer->full, t->Ringbuffer->lock);    
    }

    Ringbuffer->front->value = t->value;
    printf("enqueue %d into RingBuffer\n", t->value);
    Ringbuffer->front = Ringbuffer->front->next;
    /* Wake up empty for dequeue */
    pthread_cond_signal(t->Ringbuffer->empty);
    /* Unlock */
    pthread_mutex_unlock(t->Ringbuffer->lock);
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

    if (!t->Ringbuffer) {
        puts("Dequeue: No Ringbuffer object\n");
        return ;
    }

    Ringbuffer_t *Ringbuffer = t->Ringbuffer;
    pthread_mutex_lock(t->Ringbuffer->lock);

    /* Check buffer is empty or not */
    while (Ringbuffer->front == Ringbuffer->tail && Ringbuffer->tail->value == -1) {
        puts("dequeue: RingBuffer is empty\n");
        pthread_cond_wait(t->Ringbuffer->empty, t->Ringbuffer->lock);
    } 
    int val = Ringbuffer->tail->value;
    Ringbuffer->tail->value = -1;
    printf("%d is dequeue\n", val);
    Ringbuffer->tail = Ringbuffer->tail->next;
    pthread_cond_signal(t->Ringbuffer->full);
    pthread_mutex_unlock(t->Ringbuffer->lock);
}

/*
 *@t: thread parameter
 */
void printRingbuffer(Ringbuffer_t *Ringbuffer)
{
    if (!Ringbuffer) {
        puts("RingBuffer is not exist\n");
        return ;
    }

    if (!Ringbuffer->front) {
        puts("RingBuffer's list is mot exist\n");
        return ;
    }

    pthread_mutex_lock(Ringbuffer->lock);
    print_list(&Ringbuffer->front);
    pthread_mutex_unlock(Ringbuffer->lock);
}