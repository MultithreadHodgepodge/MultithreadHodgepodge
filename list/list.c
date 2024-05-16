#include"list.h"

list_t* create_list( list_t *head ) {
    head = MALLOC_LIST()
    head->st.w = 0;
    CONNECT_SELF( head )
    head->st.w |= STRUCT_IS_ALLOCATED;
    head->st.w |= STRUCT_IS_CREATED_BY_MALLOC;
    return head;
}

void list_add_head( list_t** list, list_t *node ){
    MUL_HODGEPODGE_ASSERT( *list, "Empty list" );
    CONNECT_PREV_NEXT( node, *list )
    node->st.w |= STRUCT_IS_ADDED;
    *list = node;
}

void list_add_tail( list_t* list,  list_t *node ){
    MUL_HODGEPODGE_ASSERT( list, "Empty list" );
    CONNECT_PREV_NEXT( node, list )
    list->prev = node;
    node->st.w |= STRUCT_IS_ADDED;
}

void list_add_in_nth_node( list_t** list, list_t *node, int n ){
    MUL_HODGEPODGE_ASSERT( *list, "Empty list" );
    list_t *temp = *list;
    int i = 0;
    while(i <= n || temp != (*list)){
        if(i == n){
            temp->prev->next = node;
            node->prev = temp->prev;
            temp->prev = node;
            node->next = temp;
            node->st.w |= STRUCT_IS_ADDED;
            break;
        }
        ++i;
        temp = temp->next;
    }
    
    MUL_HODGEPODGE_ASSERT( IsAdd( node->st.w ), "Node isn't added successfully" );
    MUL_HODGEPODGE_ASSERT( n <= i, "Node isn't added successfully because of n to big" );
    if( n==0 ) *list=node;
}

list_t* list_remove_head( list_t *list ){
    MUL_HODGEPODGE_ASSERT( list, "Empty list" );
    list_t *temp = list;
    
    if( list == list->next ){
        if( IsCreateByMalloc( list->st.w ) )free(list);
        list->st.w = 0;
        list->st.w |= STRUCT_IS_FREE;
        list = NULL;
        return list;
    }
    list->prev->next = list->next;
    list->next->prev = list->prev;
    list = list->next;
    temp->prev = NULL;
    temp->next = NULL;
    if( IsCreateByMalloc( temp->st.w ) )free(temp);
    temp->st.w = 0;
    temp->st.w |= STRUCT_IS_FREE;
    temp = NULL;
    return list;
}

void list_remove_tail( list_t *list ){
    MUL_HODGEPODGE_ASSERT( list, "List is NULL" );
    MUL_HODGEPODGE_ASSERT( IsAllocate( list->st.w ), "List isn't allocated" );
    if( list == list->next ){
        if(IsCreateByMalloc( list->st.w ))free(list);
        list->st.w = 0;
        list->st.w |= STRUCT_IS_FREE;
        list=NULL;
        return;
    }

    list_t *temp = list;
    /* A  B <->  C
     * |         |
     * - - - - - -
     */
    temp->prev = temp->prev->prev; 
    /* A  non <- C
     * |         |
     * - - - - - -
     */
    if( IsCreateByMalloc( temp->prev->next->st.w ))free(temp->prev->next);
    temp->prev->next->st.w = 0;
    temp->prev->next->st.w |= STRUCT_IS_FREE;
    /* A <-> C
     * 
     */
    temp->prev->next = temp;
}

void list_remove_nth_node( list_t **list, int n ){
    /* Check no node */
    MUL_HODGEPODGE_ASSERT(*list , "Empty list");
    if( n == 0 && *list == (*list)->next ){
        if(IsCreateByMalloc( (*list)->st.w ))free(*list);
        (*list)->st.w = 0;
        (*list)->st.w |= STRUCT_IS_FREE;
        *list = NULL;
        return;
    }
    int i=0;
    list_t *temp = *list;
    while(i <= n || temp != (*list)){
        if( i == n ){
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            list_t *to_be_free = temp;
            temp=temp->next;
            if(IsCreateByMalloc( to_be_free->st.w ))free(to_be_free);
            to_be_free->st.w = 0;
            to_be_free->st.w |= STRUCT_IS_FREE;
            break; 
        }
        ++i;
        temp = temp->next;
    }
    if(i == 0) (*list) = temp;
}


void list_remove_specific_node( list_t *list, list_t *node ){
    MUL_HODGEPODGE_ASSERT( list ,"Empty list" ); 
    while( list && (list)==node){
        if( list == list->next ){
            list->st.w = 0;
            list->st.w |= STRUCT_IS_FREE;
            if(IsCreateByMalloc( list->st.w ))free(list);
            list = NULL;
            return;
        }
        list->prev->next = list->next;
        list->next->prev = list->prev;
        list_t *temp = list;
        list = list->next;
        temp->st.w = 0;
        temp->st.w |= STRUCT_IS_FREE;
        free(temp);
        temp = NULL;
    }
    list_t *head = list;
    do{
        if( list == node ){
            list->prev->next = list->next;
            list->next->prev = list->prev;
        }
        list = list->next;
    }while( list != head );
}

void free_list( list_t *list ){
    MUL_HODGEPODGE_ASSERT( list ,"Empty list" );
    while( list != NULL ){
        list = list_remove_head( list );
    }
}