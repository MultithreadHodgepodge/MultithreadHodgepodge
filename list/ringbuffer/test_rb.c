#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include "ringbuffer.h"

Ringbuffer_t *rb = NULL;
pthread_t t1, t2, t3, t4, t5, t6;
    
void handler();

int main()
{
    threadpa_t p1, p2, p3, p4, p5, p6;
    createRingbuffer(&rb, 3);
    list_t *node1=(list_t*)malloc(sizeof(list_t)),*node2=(list_t*)malloc(sizeof(list_t)),*node3=(list_t*)malloc(sizeof(list_t));
    THREADPA_INIT(p1,Ringbuffer,node1)
    THREADPA_INIT(p2,Ringbuffer,node2)
    THREADPA_INIT(p3,Ringbuffer,node3)
    srand(time(NULL));
    
    int ret = atexit(handler);
    if (ret != 0) {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    assert(rb != NULL);

     while (1) {


        p1.value = rand() % 10 + 1;
        p2.value = rand() % 10 + 1;
        p3.value = rand() % 10 + 1;
        p4.value = rand() % 10 + 1;
        p5.value = rand() % 10 + 1;
        p6.value = rand() % 10 + 1;


        pthread_create(&t1, NULL, (void *)enqueue, &p1);
        printRingbuffer(rb);
        sleep(2);
        pthread_create(&t2, NULL, (void *)enqueue, &p2);
        pthread_create(&t3, NULL, (void *)enqueue, &p3);
        printRingbuffer(rb);
        sleep(2);
        pthread_create(&t4, NULL, (void *)dequeue, &p4);
        pthread_create(&t5, NULL, (void *)enqueue, &p5);
        printRingbuffer(rb);
        sleep(2);
        pthread_create(&t6, NULL, (void *)dequeue, &p6);
        printRingbuffer(rb);
        sleep(2);
     }
    
}

void handler()
{
    puts("\nClean mem\n");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    freeRingbuffer(&rb);
}