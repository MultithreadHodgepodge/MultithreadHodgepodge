#include"stack.h"

int main(){
    mul_stack_t *stack=NULL;
    pthread_t thread1 ,thread2,thread3;
    stack=create_stack(stack,10);
    pthread_t thread4 ,thread5,thread6;
    mul_stack_data_t *data1=pack_stack_data(stack,"I ");
    mul_stack_data_t *data2=pack_stack_data(stack,"am ");
    mul_stack_data_t *data3=pack_stack_data(stack,"BigChung ");
    pthread_create(&thread1,NULL,&PUSH_INTF,(void*)data1);
    pthread_create(&thread2,NULL,&PUSH_INTF,(void*)data2);
    pthread_create(&thread3,NULL,&PUSH_INTF,(void*)data3);
    //pthread_create(&thread4,NULL,&pop,stack);
    //pthread_create(&thread5,NULL,&pop,stack);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    //pthread_join(thread4,NULL);
    //pthread_join(thread5,NULL);
    //free_stack(&stack);
}