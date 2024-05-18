#include"hashtable.h"

int hash_func1(int value){
    return value % HASH_TABLE_SIZE;
}
int main(){
    mul_hash_t *hash=create_hash_table(77);
    set_hash_func(hash, hash_func1);
    pthread_t thread1 ,thread2,thread3, thread4, thread5;
    mul_hash_data_t *hash_data1=pack_hash_data(hash,127);
    mul_hash_data_t *hash_data2=pack_hash_data(hash,50);
    mul_hash_data_t *hash_data3=pack_hash_data(hash,50);
    mul_hash_data_t *hash_data4=pack_hash_data(hash,50);
    mul_hash_data_t *hash_data5=pack_hash_data(hash,22);
    
    
    pthread_create(&thread1,NULL,insert_hash,hash_data1);
    pthread_create(&thread2,NULL,insert_hash,hash_data2);
    pthread_create(&thread3,NULL,delete_hash,hash_data3);
    //pthread_create(&thread4,NULL,delete_hash,hash_data4);
    pthread_create(&thread5,NULL,insert_hash,hash_data5);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    print_hash(hash,50);
}