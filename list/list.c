#include"list.h"


/**
* @brief: create_list()-Create list node
* @list: A pointer to list_t
*/
list_t* create_list(list_t *head) {
    head=MALLOC_LIST()
    head->st.w=0;
    CONNECT_SELF(head)
    head->st.bit.configured=1;
    head->st.bit.is_malloc=1;
    head->st.bit.is_free=0;
    head->st.bit.is_multithread=0;
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
* @retuen: New head
*/
list_t* list_remove_head(list_t *list){
    MUL_HODGEPODGE_ASSERT(list, "Empty list");
    list_t *temp=list;
    //If only one node, and you free directly. It won't take place because the address is still in *list but the memory is freed(Segmentation Fault).
    
    if(list==list->next){
        list->st.bit.is_free=1;
        if(list->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(list);
        puts("Node is removed\n");
        list=NULL;
        return list;
    }
    list->prev->next=list->next;
    list->next->prev=list->prev;
    list=list->next;
    temp->prev=NULL;
    temp->next=NULL;
    temp->st.bit.is_free=1;
    if(temp->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(temp);
    printf("Node is removed\n");
    //perror("NN");
    temp=NULL;
    return list;
}

/**
* @brief: list_remove_tail()-Remove the list from tail
* @list: A pointer to pointer which point to list  
*/
void list_remove_tail(list_t *list){

    MUL_HODGEPODGE_ASSERT(list , "List is NULL");
    /* Check no node */
    MUL_HODGEPODGE_ASSERT(list->st.w & STRUCT_IS_ALLOCATED , "List isn't allocated");
    /* Check if only one node*/
    if(list==(list)->next){
        list->st.bit.is_free=1;
        if(list->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(list);
        list=NULL;
        puts("Node is removed\n");
        return;
    }
    /* list head */
    list_t *temp = list;
    /* A  B <->  C
     * |         |
     * - - - - - -
     */
    temp->prev=temp->prev->prev; 
    /* A  non <- C
     * |         |
     * - - - - - -
     */
    temp->prev->next->st.bit.is_free=1;
    if(temp->prev->next->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(temp->prev->next);
    /* A <-> C
     * 
     */
    temp->prev->next = temp;
    puts("Node is removed\n");
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
            list->st.w=0;
            list->st.bit.is_free=1;
            free(list);
            list=NULL;
            return;
        }
        (list)->prev->next=(list)->next;
        (list)->next->prev=(list)->prev;
        list_t *temp=(list);
        list = (list)->next;
        temp->st.w=0;
        temp->st.bit.is_free=1;
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
void free_list(list_t *list){
    MUL_HODGEPODGE_ASSERT(list , "Empty list");
    list_t *tail= (list)->prev;
    list_t *prev;
    list_t *cur =  list;
    while(cur != tail && !(cur->st.w & STRUCT_IS_FREE)) {
        prev = cur;
        cur = cur->next;
        prev->st.w=0;
        prev->st.bit.is_free=1;
        if(prev->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(prev);
        prev = NULL;
    }
    tail->st.w=0;
    tail->st.bit.is_free=1;
    if(tail->st.w & STRUCT_IS_CREATED_BY_MALLOC)free(tail);
    tail = NULL;
    list = NULL;
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