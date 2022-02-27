#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#ifndef LOCK_LIST_H__
#define LOCK_LIST_H__
typedef struct list{
    struct list* next;
    struct list* prev;
    void* value;
}list_t;
//TODO: Create List function
void list_add_head(list_t**, void*);
void list_add_tail(list_t**, void*);
void list_remove_head(list_t** );
void list_remove_tail(list_t** );
void print_list();
void free_list();
#endif