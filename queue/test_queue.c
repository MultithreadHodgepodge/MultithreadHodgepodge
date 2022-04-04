#include "queue.h"
#include <pthread.h>
#include"../common/threadpa_macro.h"
int main() 
{
    queue_t *queue = NULL;
    pthread_t t1, t2, t3, t4, t5;
    create_queue(&queue, 10);
    THREADPA_INIT(param1,queue,1)
    THREADPA_INIT(param2,queue,2)
    THREADPA_INIT(param3,queue,3)
    pthread_create(&t1, NULL, enqueue, &param1);
    pthread_create(&t2, NULL, enqueue, &param2);
    pthread_create(&t3, NULL, enqueue, &param3);
    pthread_create(&t4, NULL, dequeue, &queue);
    pthread_create(&t5, NULL, dequeue, &queue);
    
    
    //print_queue(&q);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    print_queue(&queue);


    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    print_queue(&queue);
    free_queue(&queue);
    
    // print_queue(&q);
    // free_queue(&q);
    return 0;

}