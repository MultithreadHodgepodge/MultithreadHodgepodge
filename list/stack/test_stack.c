#include"stack.h"

int main(){
    mul_stack_t *mul_stack=NULL;
    pthread_t thread1 ,thread2,thread3;
    list_t *node1=(list_t*)malloc(sizeof(list_t)),*node2=(list_t*)malloc(sizeof(list_t)),*node3=(list_t*)malloc(sizeof(list_t));

    create_stack(&mul_stack,10);
    THREADPA_INIT(param1,mul_stack,node1)
    THREADPA_INIT(param2,mul_stack,node2)
    THREADPA_INIT(param3,mul_stack,node3)
    pthread_create(&thread1,NULL,&push,&param1);
    pthread_t thread4 ,thread5,thread6;
    pthread_create(&thread4,NULL,&pop,mul_stack);
    pthread_create(&thread5,NULL,&pop,mul_stack);
    pthread_create(&thread6,NULL,&pop,mul_stack);
    pthread_create(&thread2,NULL,&push,&param2);
    pthread_create(&thread3,NULL,&push,&param3);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    pthread_join(thread6,NULL);
    free_stack(mul_stack);
}