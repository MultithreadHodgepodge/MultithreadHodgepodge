#include"stack.h"
#include<pthread.h>
#include"../common/threadpa_macro.h"
int main(){
    stack_t *stack=NULL;
    pthread_t *thread1 ,*thread2,*thread3;
    create_stack(&stack,10);
    // THREADPA_INIT(param1,stack,1)
    // THREADPA_INIT(param2,stack,2)
    // THREADPA_INIT(param3,stack,3)
    // pthread_create(&thread1,NULL,&push,&param1);
    // pthread_t thread4 ,thread5,thread6;
    // pthread_create(&thread4,NULL,&pop,stack);
    // pthread_create(&thread5,NULL,&pop,stack);
    // pthread_create(&thread6,NULL,&pop,stack);
    // pthread_create(&thread2,NULL,&push,&param2);
    // pthread_create(&thread3,NULL,&push,&param3);
    // pthread_join(thread1,NULL);
    // pthread_join(thread2,NULL);
    // pthread_join(thread3,NULL);
    // pthread_join(thread4,NULL);
    // pthread_join(thread5,NULL);
    // pthread_join(thread6,NULL);
    // print_stack(stack);
    free_stack(stack);
}