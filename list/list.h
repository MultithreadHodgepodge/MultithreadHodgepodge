#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include "../common/compare.h"
#ifndef LOCK_LIST_H__
#define LOCK_LIST_H__
/**
 * container_of() - Calculate address of object that contains address ptr
 * @ptr: pointer to member variable
 * @type: type of the structure containing ptr
 * @member: name of the member variable in struct @type
 *
 * Return: @type pointer of object containing ptr
 */
#ifndef container_of
#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })
#endif

/**
 * list_entry() - Calculate address of entry that contains list node
 * @node: pointer to list node
 * @type: type of the entry containing the list node
 * @member: name of the list_head member variable in struct @type
 */
#define list_entry(node, type, member) container_of(node, type, member)

/**
 * CONNECT_PREV_NEXT() - Connect node with prev and next node 
 * @node: pointer to list node be added
 * @list: pointer to pointer to list node(Add @node before this list node)
 */
#define CONNECT_PREV_NEXT(node,list)\
    node->prev=(*list)->prev; \
    (*list)->prev->next=node; \
    (*list)->prev=node; \
    node->next=*list; \


typedef struct list{
    struct list* next;
    struct list* prev;
}list_t;


void create_list(list_t **head);
void list_add_head(list_t**, list_t*);
void list_add_tail(list_t**, list_t*);
void list_remove_head(list_t** );
void list_remove_tail(list_t** );
void list_remove_specific_node(list_t**, list_t*);
void free_list(list_t **list);
void list_reverse(list_t **);
#endif
