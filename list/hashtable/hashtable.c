#include"hashtable.h"
/**
* @brief: create_hash_table()-Create Hashtable 
* @size: Size of Hashtable(Entry number of Hashtable)
*/
hash_t *create_hash_table(int size){
    HASH_TABLE_SIZE=size>0?size:HASH_TABLE_SIZE;
    
    hash_t *hash_table=(hash_t*)malloc(HASH_TABLE_SIZE*sizeof(hash_t));
    int i=0;
    for(i=0;i<HASH_TABLE_SIZE;i++){
        hash_table[i].key=-1;
    }
    return hash_table;
}

/**
* @brief: insert_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be added
*/
void insert_hash(hash_t *hash_table,int value){
    int key=GET_HASH_KEY(value)
    if(hash_table[key].key==-1){

        //create_list(&hash_table[key].list);
        list_t *head = &hash_table[key].list;
        CONNECT_SELF(head)
        hash_table[key].key=value;
    }
    else{

        hash_t* hash_node=(hash_t*) malloc(sizeof(hash_t));
        
        hash_node->key=value;
        //hash_node->list=(list_t*)malloc(sizeof(list_t));
        list_add_tail(&hash_table[key].list,&hash_node->list);

    }
}

/**
* @brief: delete_hash()- Insert into hashtable
* @hash_table: Pointer to hashtable
* @value: Value to be deleted
*/
void delete_hash(hash_t *hash_table,int value){
    int key=GET_HASH_KEY(value);
    assert(hash_table[key].key!=-1);
    list_t *head=&hash_table[key].list;
    hash_t *hash_node=&hash_table[key];
    do{
        if(hash_node->key==key){
            list_remove_specific_node(&hash_table[key].list,&hash_node->list);
            free(hash_node);
            break;
        }
        hash_node=list_entry(hash_node->list.next,hash_t,list);
    }while(head!=&hash_node->list);
}

/**
* @brief: print_hash()- Print given key in hashtable
* @hash_table: Pointer to hashtable
* @key: Key in hashtable
*/
void print_hash(hash_t *hash_table,int key){
    assert(key<=HASH_TABLE_SIZE);
    list_t *head=&hash_table[key].list;
    hash_t *hash_node=&hash_table[key];
    do{
        printf("Hash key: %d, Value=%d \n",key,hash_node->key);
        hash_node=list_entry(hash_node->list.next,hash_t,list);
    }while(head!=&hash_node->list);
}

