#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ringbuffer.h"

int main()
{
    Ringbuffer_t *rb = NULL;
    threadpa_t p1, p2, p3, p4, p5, p6;
    pthread_t t1, t2, t3, t4, t5, t6;
    createRingbuffer(&rb, 3);
    p1.Ringbuffer = p2.Ringbuffer = p3.Ringbuffer = p4.Ringbuffer = p5.Ringbuffer = p6.Ringbuffer = rb;
    srand(time(NULL));
    
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