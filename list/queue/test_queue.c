#include "queue.h"


int main() 
{
    mul_queue_t *queue=NULL;
    pthread_t thread1 ,thread2,thread3;
    queue=create_queue(queue,10);
    pthread_t thread4 ,thread5,thread6;
    mul_queue_data_t *data1=pack_queue_data(queue,"I ");
    mul_queue_data_t *data2=pack_queue_data(queue,"am ");
    mul_queue_data_t *data3=pack_queue_data(queue,"BigChung ");
    //pthread_create(&thread4,NULL,&dequeue,&queue);
    //pthread_create(&thread5,NULL,&dequeue,&queue);
    pthread_create(&thread1,NULL,&ENQUEUE_INTF,data1);
    pthread_create(&thread2,NULL,&ENQUEUE_INTF,data2);
    pthread_create(&thread3,NULL,&ENQUEUE_INTF,data3);
    pthread_create(&thread4,NULL,&dequeue,queue);
    pthread_create(&thread5,NULL,&dequeue,queue);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    free_queue(&queue);
    free(data1);
    free(data2);
    free(data3);
}