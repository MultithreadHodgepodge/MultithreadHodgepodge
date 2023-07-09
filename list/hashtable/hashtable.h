#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>


static int HASH_TABLE_SIZE=69;
#define GET_HASH_KEY(value)\
    value%HASH_TABLE_SIZE;

typedef struct hashtable{
    int key;
    list_t list;
    int count;
    state st;
    pthread_mutex_t *hash_lock;
}mul_hash_t;

typedef struct hashdata{
    int value;
    mul_hash_t *hashtable;
}mul_hash_data_t;

/**
* @brief: create_hash_table()-Create Hashtable 
* @size: Size of Hashtable(Entry number of Hashtable)
* @return: mul_hash_t be created
*/
mul_hash_t *create_hash_table( int );
/**
* @brief: pack_hash_data()-Pack hashtable and value into hashdata
* @hashtable: Pointer to hashtable
* @value: Value in hashdata
* @return: mul_hash_data_t be created
*/
mul_hash_data_t *pack_hash_data( mul_hash_t *, int );
/**
* @brief: insert_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be added
*/
void insert_hash( mul_hash_data_t * );
/**
* @brief: delete_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be deleted
*/
void delete_hash( mul_hash_data_t * );
/**
* @brief: print_hash()- Print given key in hashtable
* @hash_table: Pointer to hashtable
* @key: Key in hashtable
*/
void print_hash( mul_hash_t *,int );