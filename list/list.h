#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>
#include <assert.h>
#include "../common/compare.h"
#ifndef LOCK_LIST_H__
#define LOCK_LIST_H__

typedef struct list{
    struct list* next;
    struct list* prev;
    void* value;
}list_t;

void create_list(list_t **head, void *node_value);
void list_add_head(list_t**, void*);
void list_add_tail(list_t**, void*);
void list_add_before_larger_smaller(list_t**, void*,int(*compare)(const void *, const void*));
void list_remove_head(list_t** );
void list_remove_tail(list_t** );
void list_remove_specific_node(list_t**, void*);
void print_list(list_t** );
void free_list(list_t **list);
void sort(list_t **, int(*compare)(const void *, const void*));
void *list_find_max(list_t **);
void *list_find_min(list_t **);
void list_reverse(list_t **);


#endif
