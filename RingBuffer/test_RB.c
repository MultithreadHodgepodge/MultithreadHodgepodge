#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RingBuffer.h"

int main()
{
    Ringbuffer_t *rb = NULL;
    threadpa_t p1, p2, p3, p4, p5, p6;
    pthread_t t1, t2, t3, t4, t5, t6;
    createRB(&rb, 3);
    p1.rb = p2.rb = p3.rb = p4.rb = p5.rb = p6.rb = rb;
    srand(time(NULL));
    
    assert(rb != NULL);

    while (1) {


        p1.val = rand() % 10 + 1;
        p2.val = rand() % 10 + 1;
        p3.val = rand() % 10 + 1;
        p4.val = rand() % 10 + 1;
        p5.val = rand() % 10 + 1;
        p6.val = rand() % 10 + 1;


        pthread_create(&t1, NULL, (void *)enqueue, &p1);
        printRB(rb);
        sleep(2);
        pthread_create(&t2, NULL, (void *)enqueue, &p2);
        pthread_create(&t3, NULL, (void *)enqueue, &p3);
        printRB(rb);
        sleep(2);
        pthread_create(&t4, NULL, (void *)dequeue, &p4);
        pthread_create(&t5, NULL, (void *)enqueue, &p5);
        printRB(rb);
        sleep(2);
        pthread_create(&t6, NULL, (void *)dequeue, &p6);
        printRB(rb);
        sleep(2);
    }
    
}