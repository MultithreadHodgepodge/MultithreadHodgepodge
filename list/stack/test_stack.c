#include"stack.h"

int main(){
    mul_stack_t *stack=NULL;
    pthread_t thread1 ,thread2,thread3;
    stack=create_stack(stack,10);
    pthread_t thread4 ,thread5,thread6;
    pthread_create(&thread4,NULL,&pop,stack);
    pthread_create(&thread5,NULL,&pop,stack);
    pthread_create(&thread2,NULL,&push,stack);
    pthread_create(&thread3,NULL,&push,stack);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    free_stack(&stack);
}