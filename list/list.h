#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>
#include <assert.h>
#include<limits.h>
#include <stddef.h>

#ifndef LIST_H__
#define LIST_H__
#include "../common/common_struct.h"
#include "../common/compare.h"
#include "../common/mul_hodgepodge_assert.h"
#include "../common/mul_hod_malloc.h"
typedef struct list{
    struct list* next;
    struct list* prev;
    state st;
}list_t;

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
 * @list: pointer to list node(Add @node before this list node)
 */
#define CONNECT_PREV_NEXT(node,list)\
    node->prev = (list)->prev; \
    (list)->prev->next = node; \
    (list)->prev = node; \
    node->next = (list); \
    
/**
 * CONNECT_SELF() - Point node prev and next to node
 * @node: pointer to list node 
 */
#define CONNECT_SELF(node) \
    node->prev = node;\
    node->next = node;\

#if defined(MUL_HOD_UT) 
    extern list_t* create_list( list_t * );
    extern void list_add_head( list_t **, list_t * );
    extern void list_add_tail( list_t*, list_t* );
    extern void list_add_in_nth_node( list_t** ,  list_t *, int );
    extern list_t* list_remove_head( list_t* );
    extern void list_remove_tail( list_t* );
    extern list_t* list_remove_specific_node( list_t*, list_t*);
    extern void list_remove_nth_node( list_t **, int );
    extern void free_list( list_t *list );
    extern void list_reverse( list_t ** );
#else
/**
* @brief: create_list()-Create list node
* @list: A pointer to list_t
* @return: list_t be created
*/
list_t* create_list( list_t * );
/**
* @brief: list_add_head()-Add node to head of list
* @list: A pointer to pointer to list head
* @node: list_t node to be added
*/
void list_add_head( list_t **, list_t * );
/**
* @brief: list_add_tail()-Add node to tail of list
* @list: A pointer to list_t head
* @node: list_t node to be added
*/
void list_add_tail( list_t*, list_t* );
/**
* @brief: list_add_in_nth_node()-Add node to nth node of list
* @list: A pointer to pointer to list head
* @node: list_t node to be added
* @n : Index of node expect to be added
*/
void list_add_in_nth_node( list_t**, list_t *, int );
/**
* @brief: list_remove_head()-Remove the list from head
* @list: A pointer to pointer to list head
* @retuen: New head of list
*/
    list_t* list_remove_head( list_t* );
/**
* @brief: list_remove_tail()-Remove the list from tail
* @list: A pointer to pointer to list  head
*/
    void list_remove_tail( list_t* );
/**
* @brief: list_remove_specific_node()-Remove specific node from list 
* @list: A pointer to list head
* @node: list_t node to be removed
*/
    list_t* list_remove_specific_node( list_t*, list_t* );
/**
 * @brief:list_remove_nth_node(): Remove the nth node from list
 * @list: Pointer to pointer to lost head
 * @n: The nth node to be removed
*/
    void list_remove_nth_node( list_t **, int );
/**
* @brief: free_list()-Free the whole list
* @list: A pointer to list head
*/
    void free_list( list_t *list );
/**
* @brief: list_reverse()-Reverse the list
* @list: A pointer to pointer to list head
*/
    void list_reverse( list_t ** );
#endif //MUL_HOD_UT
#endif //LIST_H__