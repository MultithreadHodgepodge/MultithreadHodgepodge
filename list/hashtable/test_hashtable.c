#include"hashtable.h"
int main(){
    hash_t *hash_table=create_hash_table(77);
    insert_hash(hash_table,127);
    insert_hash(hash_table,50);
    insert_hash(hash_table,50);
    delete_hash(hash_table,50);
    insert_hash(hash_table,22);
    print_hash(hash_table,50);
}