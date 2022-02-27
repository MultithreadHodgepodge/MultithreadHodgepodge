#include"list.h"
/*
* Add node to head of list
* @list: A pointer to pointer which point to list 
* @node_value: Value of node added
*/

void Create_list(list_t **head, void *node_value) {
    if (*head) {
        printf("List Exist\n");
    } else {
        printf("List Creation\n");
        printf("Add node %p\n",node_value);
        *head=(list_t *)malloc(sizeof(list_t));
        (*head)->value=node_value;
        (*head)->prev=*head;
        (*head)->next=*head;
    }
    return ;
}

void list_add_head(list_t** list, void* node_value){
    
    if(!(*list)){
        Create_list(list, node_value);
        return ;
    }
    list_t* new_node=(list_t *)malloc(sizeof(list_t));
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
        Create_list(list, node_value);
        return;
    }
    list_t* new_node=(list_t *)malloc(sizeof(list_t));
    new_node->value=node_value;
    (*list)->prev->next=new_node;
    new_node->prev=(*list)->prev;
    new_node->next=(*list);
    (*list)->prev=new_node;
    printf("Add node %p\n",node_value);
}

/*
* Remove the list from head
* @list: A pointer to list 
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
* @list: A pointer to list 
*/
void list_remove_tail(list_t **list){
    if(!(*list)){
        printf("Empty List nothing to remove\n");
        return;
    }
    list_t *temp=(*list)->prev;
    printf("Remove node %p \n",temp->value);
    if(*list==(*list)->next){
        free(*list);
        *list=NULL;
        return;
    }
    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    temp->prev=NULL;
    temp->next=NULL;
    free(temp);
    temp=NULL;

}
/*
* Print the list
* @list: A pointer to list 
*/
void print_list(list_t** cur){
    if(!*cur){
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
* @list: A pointer to list 
*/
void free_list(list_t **list){
    if(!*list){
        printf("Nothing to free\n");
        return;
    }

    list_t *tail= (*list)->prev;
    list_t *prev = *list;
    list_t *cur = *list;
    do{
        prev = cur;
        cur = cur->next;
        free(prev);
    }while(cur != tail);

    free(tail);
    *list = NULL;
    puts("All clear");
}
