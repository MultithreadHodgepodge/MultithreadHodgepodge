#include"hashtable.h"
#include<pthread.h>
int main(){
    hash_t *hash=create_hash_table(77);
    pthread_t thread1 ,thread2,thread3, thread4, thread5;
    
    THREADPA_INIT(param1,hash,127)
    THREADPA_INIT(param2,hash,50)
    THREADPA_INIT(param3,hash,50)
    THREADPA_INIT(param4,hash,50)
    THREADPA_INIT(param5,hash,22)
    
    pthread_create(&thread1,NULL,insert_hash,&param1);
    pthread_create(&thread2,NULL,insert_hash,&param2);
    pthread_create(&thread3,NULL,insert_hash,&param3);
    pthread_create(&thread4,NULL,delete_hash,&param4);
    pthread_create(&thread5,NULL,insert_hash,&param5);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    print_hash(hash,50);
}