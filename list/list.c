#include"list.h"
#include<limits.h>

/**
* create_list()-Add node to head of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/
void create_list(list_t **head) {
    if (*head) {
        printf("List Exist\n");
    } else {
        printf("List Creation\n");
        *head=(list_t *)malloc(sizeof(list_t));
        if (!head) {
            puts("List memory allocate fail\n");
            return;
        }   
        (*head)->prev=*head;
        (*head)->next=*head;
    }
}

/**
* list_add_head()-Add node to head of list
* @list: A pointer to pointer which point to list 
* @node: Node to be added
*/
void list_add_head(list_t** list, list_t *node){
    
    if(!(*list)){
        create_list(list);
        return ;
    }

    if (!node) {
        puts("Node is empty\n");
        return ;
    }

    CONNECT_PREV_NEXT(node,list)
    *list=node;
    printf("Node is added\n");
}

/**
* list_add_tail()-Add node to tail of list
* @list: A pointer to pointer which point to list 
* @node: Node to be added
*/
void list_add_tail(list_t** list,  list_t *node){

    if(!(*list)){
        create_list(list);
        return ;
    }

    if (!node) {
        puts("Node is empty\n");
        return ;
    }
    CONNECT_PREV_NEXT(node,list)
    (*list)->prev=node;
    printf("Node is added\n");

}

/**
* list_add_after_specific_node()-Add node after specific node value in list
* @list: A pointer to pointer which point to list 
* @node: Node to be added
* @specific_node: Node which want to add after
*/
void list_add_after_specific_node(list_t** list, list_t *node, list_t *specific_node){
    if(!(*list)){
        create_list(list);
        return ;
    }
    list_t *head = *list;

    do{
        if(head==specific_node){
            printf("Node is added\n");
            node->next=head->next;
            node->prev=head;
            head->next=node;
            node->next->prev=node;
            return;
        }

        head = head->next;
    }while(head != *list);
}


/**
* list_remove_head()-Remove the list from head
* @list: A pointer to pointer which point to list 
*/
void list_remove_head(list_t **list){
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
    list_t *temp=*list;
    printf("Node is removed\n");
    //If only one node, and you free like line 70 71. It won't take place because the address is still in *list but the memory is freed(Segmentation Fault).
    //當只有一個node如果還是像第70 71行這樣雖然空間被釋放了但位址只有temp被清成NULL(*list的還存著原本的外面還是找得到位置不會是NULL)，多個node可以因為我們還需存下個node的位址，所以當一個node我們直接free(*list)再清成NULL就好
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
* list_remove_tail()-Remove the list from tail
* @list: A pointer to pointer which point to list  
*/
void list_remove_tail(list_t **list){

    /* Check no node */
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
   
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
* list_remove_specific_node()-Remove specific node value in the list 
* @list: A pointer to pointer which point to list  
* @node: Node to be removed
*/

void list_remove_specific_node(list_t **list, list_t *node){
    /* Check no node */
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
   

    
    while((*list) && (*list)==node){
        printf("Node is removed\n");
        if(*list==(*list)->next){
            free(*list);
            *list=NULL;
            return;
        }
        (*list)->prev->next=(*list)->next;
        (*list)->next->prev=(*list)->prev;
        list_t *temp=(*list);
        *list = (*list)->next;
        //list = &(*list)->next;
        free(temp);
        temp = NULL;
    }
    
    list_t *head = *list;
    do{
        if((*list)==node){
            printf("Node is removed\n");
            (*list)->prev->next=(*list)->next;
            (*list)->next->prev=(*list)->prev;

        }

        *list = (*list)->next;
    }while(*list != head);
*list=head;
}


/**
* free_list()-Free the list
* @list: A pointer to pointer which point to list  
*/
void free_list(list_t **list){
    if(!*list) {
        printf("Nothing to free\n");
        return;
    }

    list_t *tail= (*list)->prev;
    list_t *prev = *list;
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
* list_reverse()-Reverse the list
* @list: A pointer to pointer which point to list  
*/
void list_reverse(list_t **list){
    if(!(*list)) {
        printf("List doesn't exist");
        return;
    }
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