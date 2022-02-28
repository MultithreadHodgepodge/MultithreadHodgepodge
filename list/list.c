#include"list.h"
/*
* Add node to head of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/

void create_list(list_t **head, void *node_value) {
    if (*head) {
        printf("List Exist\n");
    } else {
        printf("List Creation\n");
        printf("Add node %p\n",node_value);
        *head=(list_t *)malloc(sizeof(list_t));
        if (!head) {
            puts("List memory allocate fail\n");
            return;
        }   
        (*head)->value=node_value;
        (*head)->prev=*head;
        (*head)->next=*head;
    }
    return ;
}

/*
* Add node to head of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/
void list_add_head(list_t** list, void* node_value){
    
    if(!(*list)){
        create_list(list, node_value);
        return ;
    }
    list_t* new_node=(list_t *)malloc(sizeof(list_t));
    if (!new_node) {
        puts("list add head memory allocate fail");
        return ;
    }
    new_node->value=node_value;
    new_node->prev=(*list)->prev;
    (*list)->prev->next=new_node;
    (*list)->prev=new_node;
    new_node->next=*list;
    *list=new_node;
    printf("Add node %p\n",node_value);
}

/*
* Add node to tail of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/
void list_add_tail(list_t** list, void* node_value){

    if(!(*list)){
        create_list(list, node_value);
        return;
    }
    list_t* new_node=(list_t *)malloc(sizeof(list_t));
    if (!new_node) {
        puts("list add tail memory allocate fail");
        return ;
    }
    new_node->value=node_value;
    (*list)->prev->next=new_node;
    new_node->prev=(*list)->prev;
    new_node->next=(*list);
    (*list)->prev=new_node;
    printf("Add node %p\n",node_value);
}

/*
* Remove the list from head
* @list: A pointer to pointer which point to list 
*/
void list_remove_head(list_t **list){
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
    list_t *temp=*list;
    printf("Remove node %p \n",temp->value);
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
/*
* Remove the list from tail
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
        printf("Remove node %p \n",(*list)->value);
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
    printf("Remove node %p \n",temp->prev->next->value);
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
/*
/*
* Remove specific node value in the list 
* @list: A pointer to pointer which point to list  
*/

void list_remove_specific_node(list_t **list, void *value){
    /* Check no node */
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
   

    
    while((*list) && (*list)->value==value){
        printf("Remove node %p \n",(*list)->value);
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
    }
    
    list_t *head = *list;
    do{
        if((*list)->value==value){
            printf("Remove node %p \n",(*list)->value);
            (*list)->prev->next=(*list)->next;
            (*list)->next->prev=(*list)->prev;

        }

        *list = (*list)->next;
    }while(*list != head);
*list=head;
}
/*
* Print the list
* @list: A pointer to pointer which point to list  
*/
void print_list(list_t** cur){
    if(!(*cur)){
        printf("Empty List\n");
        return;
    }
    list_t *head = *cur;
    do{
        printf("%p\n",(*cur)->value);
        cur = &(*cur)->next;
    }while(*cur != head);
}
/*
* Free the list
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
    }
    free(tail);
    *list = NULL;
    puts("All clear");
}


void sort(list_t **head, int( *compare)(const void *, const void *)) 
{   
    void mergesort(list_t **, int(*)(const void *, const void *));

    /* quntity below 2 skip sort */
    if (!*head || !(*head)->next) 
        return ;

    /* make list be not circular */
    (*head)->prev->next = NULL;
    

    mergesort(head, compare);
    
    /* find tail */
    list_t *tail = *head;
    while(tail->next) {
        tail = tail->next;
    }
    
    /* make list be circular */
    (*head)->prev= tail;
    tail->next = (*head);
}

void mergesort(list_t **head, int (*compare)(const void *, const void *)) 
{

    /* use fast slow pointer method */

    if (!*head || !((*head)->next)) { 
        return ;
    }

    list_t *slow = *head;
    list_t *fast = (*head)->next;

    /* find middle node */
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    /* break into two list */
    fast = slow->next;
    slow->next = NULL;
    slow = *head;

    mergesort(&slow, compare);
    mergesort(&fast, compare);


    /* phase merge */
    list_t **list = head;
    list_t **stub = NULL;
    for (list_t **node = NULL;slow && fast;list = &(*list)->next) {
        /* take the bigger one */
        node = (compare(&slow->value, &fast->value) < 0)?&slow:&fast;
        /* list is current next pointer address ,and node is the bigger node address
        *  dereference these two pointer will be like
        *  currentNode->next = biggerNode
        */
        *list = *node;
        /* make biggerNode->prev = currentNode */
        (*node)->prev = *list;
        /* renew biggerNode to the next node */
        *node = (*node)->next;
    }
    /* Let last of node connect currentNextPointer*/
    (*list) = (list_t *)((uintptr_t )slow | (uintptr_t )fast);
}



