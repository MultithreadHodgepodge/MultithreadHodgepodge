#include"hashtable.h"
hash_t *create_hash_table(int size){
    size=size>0?size:HASH_TABLE_SIZE;
    hash_t *hash_table=(hash_t*)malloc(size*sizeof(hash_t));
    return hash_table;
}