#ifndef LIST_H__
#include "../list.h"
#endif
#include <pthread.h>

typedef struct hash_node{
    int value;
    list_t list;
}hash_node_t;

typedef struct hash_entry{
    int key;
    int count;
    hash_node_t *node;
    pthread_mutex_t *hash_lock;
}hash_entry_t;

typedef struct hashtable{
    hash_entry_t *hash_entry;
    int (*hash_func)(int);
    state st;
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
* @brief: set_hash_func()-Create Hashtable 
* @hash_func: Hash functoin that are going to be used
* @return: mul_hash_t be created
*/
void set_hash_func( mul_hash_t *, int (*)(int) );
/**
* @brief: pack_hash_data()-Pack hashtable and value into hashdata
* @hashtable: Pointer to hashtable
* @value: Value in hashdata
* @return: mul_hash_data_t be created
*/
mul_hash_data_t *pack_hash_data( mul_hash_t *, int );
/**
* @brief: Interface for pthread calling insert_hash
*/
void INSERT_HASH_INTF(mul_hash_data_t *);
/**
* @brief: insert_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be added
*/
void insert_hash( mul_hash_t * , int );
/**
* @brief: Interface for pthread calling delete_hash
*/
void DELETE_HASH_INTF(mul_hash_data_t *);
/**
* @brief: delete_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be deleted
*/
void delete_hash( mul_hash_t * , int);
/**
* @brief: print_hash()- Print given key in hashtable
* @hash_table: Pointer to hashtable
* @key: Key in hashtable
*/
void print_hash( mul_hash_t *,int );