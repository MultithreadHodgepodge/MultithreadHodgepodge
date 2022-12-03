#include"hashtable.h"
hash_t *create_hash_table(int size){
    HASH_TABLE_SIZE=size>0?size:HASH_TABLE_SIZE;
    
    hash_t *hash_table=(hash_t*)malloc(HASH_TABLE_SIZE*sizeof(hash_t));
    int i=0;
    for(i=0;i<HASH_TABLE_SIZE;i++){
        hash_table[i].key=-1;
        hash_table[i].list=NULL;
    }
    return hash_table;
}

void insert_hash(hash_t *hash_table,int value){
    int key=value%HASH_TABLE_SIZE;
    if(hash_table[key].key==-1){
        create_list(&hash_table[key].list);
        hash_table[key].key=value;
    }
    else{
        hash_t* hash_node=(hash_t*) malloc(sizeof(hash_t));
        hash_node->key=value;
        list_add_tail(hash_table[key].list,hash_node->list);
    }
}
//Not test yet
void print_hash(hash_t *hash_table,int key){
    if(key>HASH_TABLE_SIZE){
        printf("Input Kry Exceeds Limitation!!!!!\n");
        return;
    }
    list_t *head=hash_table[key].list;
    hash_t *hash_node=&hash_table[key];
    do{
        printf("Hash key: %d, Value=%d \n",key,hash_node->key);
        hash_node=list_entry(hash_node->list->next,hash_t,list);
    }while(head!=hash_node->list);
}