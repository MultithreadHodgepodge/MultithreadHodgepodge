#include"hashtable.h"

/**
* @brief: create_hash_table()-Create Hashtable 
* @size: Size of Hashtable(Entry number of Hashtable)
*/
mul_hash_t *create_hash_table(int size){
    HASH_TABLE_SIZE=size>0?size:HASH_TABLE_SIZE;
    mul_hash_t *hash_table=(mul_hash_t*)malloc(HASH_TABLE_SIZE*sizeof(mul_hash_t));
    int i=0;
    for(i=0;i<HASH_TABLE_SIZE;i++){
        hash_table[i].key=-1;
        hash_table[i].hash_lock=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(hash_table[i].hash_lock,NULL);
    }
    return hash_table;
}

/**
* @brief: pack_hash_data()-Pack hashtable and value into hashdata
* @hashtable: Pointer to hashtable
* @value: Value in hashdata
*/
mul_hash_data_t *pack_hash_data(mul_hash_t *hashtable, int value){
    mul_hash_data_t *hash_data=(mul_hash_data_t*)malloc(sizeof(mul_hash_data_t));
    hash_data->hashtable=hashtable;
    hash_data->value=value;
    return hash_data;
}

/**
* @brief: insert_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be added
*/
void insert_hash(mul_hash_data_t *hash_data){
    mul_hash_t *hash_table=hash_data->hashtable;
    int value=hash_data->value;
    int key=GET_HASH_KEY(value)
    pthread_mutex_lock(hash_table[key].hash_lock);
    if(hash_table[key].key==-1){
        list_t *head = &hash_table[key].list;
        CONNECT_SELF(head)
        hash_table[key].key=value;
    }
    else{
        mul_hash_t* hash_node=(mul_hash_t*) malloc(sizeof(mul_hash_t));    
        hash_node->key=value;
        list_add_tail(&hash_table[key].list,&hash_node->list);
    }
    pthread_mutex_unlock(hash_table[key].hash_lock);
}

/**
* @brief: delete_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be deleted
*/
void delete_hash(mul_hash_data_t *hash_data){
    mul_hash_t *hash_table=hash_data->hashtable;
    int value=hash_data->value;
    int key=GET_HASH_KEY(value);
    pthread_mutex_lock(hash_table[key].hash_lock);
    MUL_HODGEPODGE_ASSERT(hash_table[key].key!=-1, "Key not existed in hashtable");
    list_t *head=&hash_table[key].list;
    mul_hash_t *hash_node=&hash_table[key];
    do{
        if(hash_node->key==key){
            list_remove_specific_node(&hash_table[key].list,&hash_node->list);
            free(hash_node);
            break;
        }
        hash_node=list_entry(hash_node->list.next,mul_hash_t,list);
    }while(head!=&hash_node->list);
    pthread_mutex_unlock(hash_table[key].hash_lock);
}

/**
* @brief: print_hash()- Print given key in hashtable
* @hash_table: Pointer to hashtable
* @key: Key in hashtable
*/
void print_hash(mul_hash_t *hash_table,int key){
    MUL_HODGEPODGE_ASSERT(key<=HASH_TABLE_SIZE, "key not exist in hash_table");
    list_t *head=&hash_table[key].list;
    mul_hash_t *hash_node=&hash_table[key];
    do{
        printf("Hash key: %d, Value=%d \n",key,hash_node->key);
        hash_node=list_entry(hash_node->list.next,mul_hash_t,list);
    }while(head!=&hash_node->list);
}

