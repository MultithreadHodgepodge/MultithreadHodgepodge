#include "queue.h"


int main() 
{
    mul_queue_t *queue = NULL;
    pthread_t t1, t2, t3, t4, t5;
    queue=create_queue(queue, 10);
    pthread_create(&t1, NULL, &enqueue, queue);
    pthread_create(&t2, NULL, &enqueue, queue);
    pthread_create(&t3, NULL, &enqueue, queue);
    pthread_create(&t4, NULL, &dequeue, &queue);
    pthread_create(&t5, NULL, &dequeue, &queue);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    free_queue(queue);
    return 0;
}