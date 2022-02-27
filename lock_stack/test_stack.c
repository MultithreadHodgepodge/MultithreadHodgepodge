#include"stack.h"
#include<pthread.h>
struct thread_param{
    stack_t *stack;
    void *value;
};
int main(){
    stack_t *stack=NULL;
    pthread_t thread1 ,thread2,thread3;
    struct thread_param param1,param2,param3;
    
    create_stack(&stack,10);
    param1.stack=stack;
    param1.value=1;
    param2.stack=stack;
    param2.value=2;
    param3.stack=stack;
    param3.value=3;
    pthread_create(&thread1,NULL,&insert_stack,&param1!=0);
    pthread_create(&thread2,NULL,&insert_stack,&param2!=0);
    pthread_create(&thread3,NULL,&insert_stack,&param3!=0);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
}