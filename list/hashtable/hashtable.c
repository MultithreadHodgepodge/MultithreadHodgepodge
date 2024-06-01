#include"hashtable.h"
static int HASH_TABLE_SIZE=69;

int default_hash_func(int value){
    return value % HASH_TABLE_SIZE;
}

mul_hash_t* create_hash_table( int size ){
    HASH_TABLE_SIZE = (size > 0) ? size : HASH_TABLE_SIZE;
    mul_hash_t *hash_table = (mul_hash_t*)malloc( sizeof(mul_hash_t) );
    int i = 0;
    hash_table->hash_func = default_hash_func;
    hash_table->st.w = 0;
    hash_table->st.w |= STRUCT_IS_ALLOCATED;
    hash_table->st.w |= STRUCT_IS_CREATED_BY_MALLOC;
    hash_table->st.w |= STRUCT_IS_MULTITHREAD;
    hash_table->hash_entry = (hash_entry_t*)malloc(sizeof(hash_entry_t) * HASH_TABLE_SIZE);
    for( i=0; i < HASH_TABLE_SIZE; i++ ){
        hash_table->hash_entry[i].key = i;
        hash_table->hash_entry[i].count = 0;
        hash_table->hash_entry[i].node = NULL;
        hash_table->hash_entry[i].hash_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init( hash_table->hash_entry[i].hash_lock, NULL );
    }
    return hash_table;
}

hash_node_t* create_hash_node(int value){
    hash_node_t *new_hash_node = (hash_node_t*)malloc( sizeof(hash_node_t) );
    new_hash_node->value = value;
    list_t *head = &(new_hash_node->list);
    CONNECT_SELF(head)
    head->st.w = 0;
    return new_hash_node;
}
void set_hash_func(mul_hash_t *hashtable, int (*hash_func)(int)){
    hashtable->hash_func = hash_func;
}

mul_hash_data_t* pack_hash_data( mul_hash_t *hashtable, int value ){
    mul_hash_data_t *hash_data = (mul_hash_data_t*)malloc( sizeof(mul_hash_data_t) );
    hash_data->hashtable = hashtable;
    hash_data->value = value;
    return hash_data;
}

void INSERT_HASH_INTF(mul_hash_data_t *hash_data){
    mul_hash_t *hash_table = hash_data->hashtable;
    int value = hash_data->value;
    insert_hash(hash_table, value);
}

void insert_hash( mul_hash_t* hash_table, int value ){
    int key = INT_MAX;
    key = hash_table->hash_func(value);
    MUL_HODGEPODGE_ASSERT(key != INT_MIN, "Hash function has problem");
    
    pthread_mutex_lock( hash_table->hash_entry[key].hash_lock );
    hash_entry_t *hash_entry = &hash_table->hash_entry[key];
    hash_node_t *new_hash_node = create_hash_node(value);
    if( hash_entry->count == 0 ){
        hash_entry->node = new_hash_node;
    }
    else{
        list_add_tail( &(hash_entry->node->list), &(new_hash_node->list) );
    }
    hash_entry->count++;
    pthread_mutex_unlock( hash_table->hash_entry[key].hash_lock );

}

void DELETE_HASH_INTF(mul_hash_data_t *hash_data){
    mul_hash_t *hash_table = hash_data->hashtable;
    int value = hash_data->value;
    delete_hash(hash_table, value);
}

void delete_hash( mul_hash_t* hash_table, int value ){
    int key = INT_MIN;
    key = hash_table->hash_func(value);
    MUL_HODGEPODGE_ASSERT(key != INT_MIN, "Hash function has problem");
    
    pthread_mutex_lock( hash_table->hash_entry[key].hash_lock );
    hash_entry_t *hash_entry = &hash_table->hash_entry[key];
    hash_node_t *hash_node_temp = NULL;
    if(hash_entry->node == NULL){
        /* No node in requested entry release mutex lock and return */
        pthread_mutex_unlock( hash_entry->hash_lock );
        return;
    }
    int i = 0;
    hash_node_temp = hash_entry->node;
    for(i = 0; i < hash_entry->count; i++){
        if(hash_node_temp->value == value){
            hash_entry->count--;
            list_t *temp = list_remove_specific_node(&hash_entry->node->list, &hash_node_temp->list);
            hash_entry->node = (temp == NULL)? NULL : list_entry(temp, hash_node_t, list);
            free(hash_node_temp);
            break;
        }
        hash_node_temp = list_entry((hash_node_temp->list.next), hash_node_t, list);
    }
    pthread_mutex_unlock( hash_table->hash_entry[key].hash_lock );
}

void print_hash( mul_hash_t *hash_table,int key ){
    MUL_HODGEPODGE_ASSERT( key <= HASH_TABLE_SIZE, "key not exist in hash_table" );
    hash_entry_t *hash_entry = &hash_table->hash_entry[key];
    int i = 0;
    printf("Hash table key: %d has total : %d element with below value in table:", key, hash_entry->count);
    hash_node_t *hash_node_temp = hash_entry->node;
    for(i=0; i < hash_entry->count; i++){
        printf(" %d ",hash_node_temp->value);
        hash_node_temp = list_entry(hash_node_temp->list.next, hash_node_t, list);
    }
    printf("\n");
}

void free_hash(mul_hash_t **hash_table){
    MUL_HODGEPODGE_ASSERT( IsAllocate( (*hash_table)->st.w), "Hashtable not allocated" );
    int i = 0, j = 0;
    for( i=0; i < HASH_TABLE_SIZE; i++ ){
        hash_entry_t *temp_entry = &((*hash_table)->hash_entry[i]);
        for(j = 0; j < temp_entry->count; j++){
            hash_node_t *temp = temp_entry->node;
            list_t *new_head = list_remove_head(&(temp->list));
            temp_entry->node = (new_head == NULL)? NULL : list_entry(new_head, hash_node_t, list);
            temp_entry->count--;
            free(temp);
        }
        free(temp_entry->hash_lock);
    }
    free((*hash_table)->hash_entry);
    free(*hash_table);
}
