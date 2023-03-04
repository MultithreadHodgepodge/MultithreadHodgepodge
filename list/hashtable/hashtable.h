#include "../list.h"
#include <pthread.h>
#include "../../common/test_macro.h"
#include"../../common/threadpa_macro.h"

static int HASH_TABLE_SIZE=69;
#define GET_HASH_KEY(value)\
    value%HASH_TABLE_SIZE;

typedef struct hashtable{
    int key;
    list_t list;
    pthread_mutex_t *hash_lock;
}mul_hash_t;

DECLARE_THREAD(mul_hash,int)
mul_hash_t *create_hash_table(int);
void insert_hash(threadpa_t *);
void delete_hash(threadpa_t *);
void print_hash(mul_hash_t*,int);