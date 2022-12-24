#include "../list.h"
#include <pthread.h>
static int HASH_TABLE_SIZE=69;
typedef struct hashtable{
    int key;
    list_t list;
}hash_t;
hash_t *create_hash_table(int);
void insert_hash(hash_t*, int);
void print_hash(hash_t *,int);