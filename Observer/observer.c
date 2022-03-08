#include"observer.h"
void observer_constructor(observer_t **observer){
    if((*observer)){
        printf("------Observer Already Exists------\n");
        return;
    }
    *observer=(observer_t *)malloc(sizeof(observer_t));
}

pthread_t *create_thread(observer *observer,void (*thread_func)(struct thread_param *),struct thread_param *param){
    //TODO:Implement It!!!
}   