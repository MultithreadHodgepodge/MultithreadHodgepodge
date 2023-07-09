#include"list.h"

list_t* create_list( list_t *head ) {
    head = MALLOC_LIST()
    head->st.w = 0;
    CONNECT_SELF( head )
    head->st.bit.configured = 1;
    head->st.bit.is_malloc = 1;
    head->st.bit.is_free= 0 ;
    head->st.bit.is_multithread =0 ;
    return head;
}

void list_add_head( list_t** list, list_t *node ){
    MUL_HODGEPODGE_ASSERT( *list, "Empty list" );
    CONNECT_PREV_NEXT( node, *list )
    node->st.bit.is_added = 1;
    *list = node;
}

void list_add_tail( list_t* list,  list_t *node ){
    MUL_HODGEPODGE_ASSERT( list, "Empty list" );
    CONNECT_PREV_NEXT( node, list )
    list->prev = node;
    node->st.bit.is_added = 1;
}

void list_add_in_nth_node( list_t** list, list_t *node, int n ){
    MUL_HODGEPODGE_ASSERT( *list, "Empty list" );
    list_t *temp = *list;
    int counter = 0;
    do{
        if( counter != n ){
            temp = temp->next;
            if( temp==*list ) break;
            counter++;
            continue;
        }
        temp->prev->next = node;
        node->prev = temp->prev;
        temp->prev = node;
        node->next = temp;
        node->st.bit.is_added = 1;
        counter++;
    }while( temp == (*list) );
    MUL_HODGEPODGE_ASSERT( IsAdd( node->st.w ), "Node isn't added successfully" );
    MUL_HODGEPODGE_ASSERT( n<=counter, "Node isn't added successfully because of n to big" );
    if( n==0 ) *list=node;
}

list_t* list_remove_head( list_t *list ){
    MUL_HODGEPODGE_ASSERT( list, "Empty list" );
    list_t *temp = list;
    if( list == list->next ){
        list->st.bit.is_free = 1;
        if( IsCreateByMalloc( list->st.w ) )free(list);
        list = NULL;
        return list;
    }
    list->prev->next = list->next;
    list->next->prev = list->prev;
    list = list->next;
    temp->prev = NULL;
    temp->next = NULL;
    temp->st.w = 0;
    temp->st.bit.is_free = 1;
    if( IsCreateByMalloc( temp->st.w ) )free(temp);
    temp = NULL;
    return list;
}

void list_remove_tail( list_t *list ){
    MUL_HODGEPODGE_ASSERT( list, "List is NULL" );
    MUL_HODGEPODGE_ASSERT( IsAllocate( list->st.w ), "List isn't allocated" );
    if( list == list->next ){
        list->st.bit.is_free=1;
        if(IsCreateByMalloc( list->st.w ))free(list);
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
    temp->prev->next->st.bit.is_free = 1;
    if( IsCreateByMalloc( temp->prev->next->st.w ))free(temp->prev->next);
    /* A <-> C
     * 
     */
    temp->prev->next = temp;
    //puts("Node is removed\n");
}

void list_remove_nth_node( list_t **list, int n ){
    /* Check no node */
    MUL_HODGEPODGE_ASSERT(*list , "Empty list");
    if( n == 0 && *list == (*list)->next ){
        (*list)->st.w = 0;
        (*list)->st.bit.is_free = 1;
        free(*list);
        *list = NULL;
        return;
    }
    int i;
    list_t *temp = *list;
    for( i=0; i<=n; i++ ){
        MUL_HODGEPODGE_ASSERT(temp!=*list, "Input n exceeds list");
        if( i == n ){
            (*list)->st.w = 0;
            (*list)->st.bit.is_free = 1;
            (*list)->next->prev = (*list)->prev;
            (*list)->prev->next = (*list)->next;
            if( i == 0 ){
                *list = (*list)->next;
            }
            return; 
        }
        temp = temp->next;
    }
    
}


void list_remove_specific_node( list_t *list, list_t *node ){
    MUL_HODGEPODGE_ASSERT( list ,"Empty list" ); 
    while( list && (list)==node){
        if( list == list->next ){
            list->st.w = 0;
            list->st.bit.is_free = 1;
            free(list);
            list = NULL;
            return;
        }
        list->prev->next = list->next;
        list->next->prev = list->prev;
        list_t *temp = list;
        list = list->next;
        temp->st.w = 0;
        temp->st.bit.is_free = 1;
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
    while( list!=NULL ){
        list->st.w = 0;
        list->st.bit.is_free = 1;
        list = list_remove_head( list );
    }
}

void list_reverse( list_t **list ){
    MUL_HODGEPODGE_ASSERT( *list ,"Empty list" );
    list_t *last = (*list)->prev;
    if( last==(*list) ) return;

    do{
        list_t *next = (*list)->next;
        (*list)->next = (*list)->prev;
        (*list)->prev = next;
        if( next == last ){
            next->prev = next->next;
            next->next = (*list);
        }
        *list = (*list)->prev;
    }while( *list != last );
}