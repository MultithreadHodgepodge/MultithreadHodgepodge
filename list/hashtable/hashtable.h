#include "../list.h"
#include <pthread.h>
#define VALUE_LIST_NUM 10
#define HASH_TABLE_SIZE 69 
typedef struct hashtable{
    int key;
    list_t value_list[VALUE_LIST_NUM];
}hash_t;
hash_t *create_hash_table(int);