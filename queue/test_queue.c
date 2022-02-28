#include "queue.h"
#include <pthread.h>

int main() 
{
    queue_t *q = NULL;
    pthread_t t1, t2, t3;
    threadpa_t param1, param2, param3;
    create_queue(&q, 10);
    param1.queue = q;
    param2.queue = q;
    param3.queue = q;
    param1.val = 10;
    param2.val = 20;
    param3.val = 30;

    pthread_create(&t1, NULL, enqueue, &param1);
    pthread_create(&t2, NULL, enqueue, &param2);
    pthread_create(&t3, NULL, enqueue, &param3);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t1, NULL);
    print_queue(&q);
    pthread_create(&t1, NULL, dequeue, &q);
    pthread_create(&t2, NULL, dequeue, &q);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    print_queue(&q);
    free_queue(&q);
    return 0;

}