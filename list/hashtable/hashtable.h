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

mul_hash_t *create_hash_table(int);
mul_hash_data_t *pack_hash_data(mul_hash_t *, int);
void insert_hash(mul_hash_data_t *);
void delete_hash(mul_hash_data_t *);
void print_hash(mul_hash_t *,int);