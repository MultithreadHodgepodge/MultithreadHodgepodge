#include"list.h"


/**
* @brief: create_list()-Add node to head of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/
list_t* create_list(list_t *head) {
    MUL_HODGEPODGE_ASSERT(!head , "List already Existed");
    puts("List Creation\n");
    head=MALLOC_LIST()
    MUL_HODGEPODGE_ASSERT(head , "Allocate list head fail");
    CONNECT_SELF(head)
    return head;
}

/**
* @brief: list_add_head()-Add node to head of list
* @list: A pointer to pointer which point to list 
* @node: Node to be added
*/
void list_add_head(list_t** list, list_t *node){
    CONNECT_PREV_NEXT(node,*list)
    *list=node;
    printf("Node is added\n");
}

/**
* @brief: list_add_tail()-Add node to tail of list
* @list: A pointer to pointer which point to list 
* @node: Node to be added
*/
void list_add_tail(list_t* list,  list_t *node){
    CONNECT_PREV_NEXT(node,list)
    (list)->prev=node;
    puts("Node is added\n");

}



/**
* @brief: list_remove_head()-Remove the list from head
* @list: A pointer to pointer which point to list 
*/
void list_remove_head(list_t **list){
    MUL_HODGEPODGE_ASSERT(*list!=NULL , "Empty list");
    list_t *temp=*list;
    printf("Node is removed\n");
    //If only one node, and you free directly. It won't take place because the address is still in *list but the memory is freed(Segmentation Fault).
    if(*list==(*list)->next){
        free(*list);
        *list=NULL;
        return;
    }
    (*list)->prev->next=(*list)->next;
    (*list)->next->prev=(*list)->prev;
    (*list)=(*list)->next;
    temp->prev=NULL;
    temp->next=NULL;
    free(temp); //WHY before temp=NULL? If set temp to NULL first,it won't point to the same location as *list
    temp=NULL;
}

/**
* @brief: list_remove_tail()-Remove the list from tail
* @list: A pointer to pointer which point to list  
*/
void list_remove_tail(list_t **list){

    /* Check no node */
    MUL_HODGEPODGE_ASSERT(*list , "Empty list");
    /* Check if only one node*/
    if(*list==(*list)->next){
        printf("Node is removed\n");
        free(*list);
        *list=NULL;
        return;
    }
    /* list head */
    list_t *temp = *list;
    /* A  B <->  C
     * |         |
     * - - - - - -
     */
    temp->prev=temp->prev->prev; 
    printf("Node is removed\n");
    /* A  non <- C
     * |         |
     * - - - - - -
     */
    free(temp->prev->next);
    /* A <-> C
     * 
     */
    temp->prev->next = temp;
}

/**
* @brief: list_remove_specific_node()-Remove specific node value in the list 
* @list: A pointer to pointer which point to list  
* @node: Node to be removed
*/
void list_remove_specific_node(list_t *list, list_t *node){
    /* Check no node */
    MUL_HODGEPODGE_ASSERT(list!=NULL , "Empty list"); 
    while((list) && (list)==node){
        printf("Node is removed\n");
        if(list==(list)->next){
            free(list);
            list=NULL;
            return;
        }
        (list)->prev->next=(list)->next;
        (list)->next->prev=(list)->prev;
        list_t *temp=(list);
        list = (list)->next;
        free(temp);
        temp = NULL;
    }
    list_t *head = list;
    do{
        if((list)==node){
            printf("Node is removed\n");
            (list)->prev->next=(list)->next;
            (list)->next->prev=(list)->prev;
        }
        list = (list)->next;
    }while(list != head);
}

/**
* @brief: free_list()-Free the list
* @list: A pointer to pointer which point to list  
*/
void free_list(list_t **list){
    MUL_HODGEPODGE_ASSERT(*list , "Empty list");
    list_t *tail= (*list)->prev;
    list_t *prev;
    list_t *cur =  *list;
    while(cur != tail) {
        prev = cur;
        cur = cur->next;
        free(prev);
        prev = NULL;
    }
    free(tail);
    tail = NULL;
    *list = NULL;
    puts("All clear");
}



/**
* @brief: list_reverse()-Reverse the list
* @list: A pointer to pointer which point to list  
*/
void list_reverse(list_t **list){
    assert(*list && "Empty list");
    list_t *last=(*list)->prev;
    if(last==(*list)) return;

    do{
        list_t *next=(*list)->next;
        (*list)->next=(*list)->prev;
        (*list)->prev=next;
        if(next==last){
            next->prev=next->next;
            next->next=(*list);
        }
        *list=(*list)->prev;
    }while(*list!=last);
    //*list=last;
}