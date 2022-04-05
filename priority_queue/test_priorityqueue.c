#include"priority_queue.h"
#include"../common/threadpa_macro.h"
int main()
{
    priority_queue_t *priority_queue=NULL;
    pthread_t t1, t2, t3, t4, t5;
    create_priority_queue(&priority_queue,10);
    THREADPA_INIT(param1,priority_queue,1)
    THREADPA_INIT(param2,priority_queue,3)
    THREADPA_INIT(param3,priority_queue,2)
    pthread_create(&t1, NULL, enqueue, &param1);
    pthread_create(&t2, NULL, enqueue, &param2);
    pthread_create(&t3, NULL, enqueue, &param3);
    pthread_create(&t4, NULL, dequeue, &priority_queue);
    pthread_create(&t5, NULL, dequeue, &priority_queue);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    print_queue(&priority_queue);
}