#include "queue.h"

mul_queue_t* create_queue( mul_queue_t *queue, int qun ) 
{
    MUL_HODGEPODGE_ASSERT( !queue, "Stack is Existed" );
    queue = MALLOC_MUL_T(queue)
    MUL_HODGEPODGE_ASSERT( queue, "Stack Memory allocated fail" );
    queue->head = NULL;
    queue->count = 0;
    queue->capacity = qun;
    queue->enqueue = list_add_tail;
    queue->dequeue = list_remove_head;
    queue->freeQueue = free_list;

    queue->queue_lock = (pthread_mutex_t*)malloc( sizeof(pthread_mutex_t) );
    queue->qremain = (sem_t*)malloc( sizeof(sem_t) );
    queue->qitem = (sem_t*)malloc( sizeof(sem_t) );
    sem_init( queue->qremain, 0, qun );
    sem_init( queue->qitem,  0, 0 );
    pthread_mutex_init( queue->queue_lock, NULL );

    queue->st.w = 0;
    queue->st.bit.configured = 1;
    queue->st.bit.is_malloc = 1;
    queue->st.bit.is_free = 0;
    queue->st.bit.is_multithread = 1;
    queue->st.bit.is_head = 1;
    return queue;
}

queue_node_t* create_queue_node( void *value ){
    queue_node_t *queue_node = MALLOC_NODE_T(queue)
    list_t *temp = &queue_node->list;
    CONNECT_SELF( temp );
    queue_node->st.w = 0;
    queue_node->st.bit.configured = 1;
    queue_node->st.bit.is_malloc = 1;
    queue_node->list.st.w = 0;
    queue_node->list.st.bit.configured = 1;
    queue_node->list.st.bit.is_malloc = 0;
    queue_node->value = value;
    return queue_node;
}

mul_queue_data_t* pack_queue_data(mul_queue_t *queue, void *value){
    MUL_HODGEPODGE_ASSERT( IsAllocate( queue->st.w ), "Queue not allocated" );
    mul_queue_data_t *queue_data = MALLOC_MUL_T(queue_data)
    queue_data->queue = queue;
    queue_data->value = value;
    return queue_data;
}


void enqueue( mul_queue_t *queue, void* value ){
    MUL_HODGEPODGE_ASSERT( IsAllocate( queue->st.w ), "Queue not allocated(enqueue)" );
    MUL_HODGEPODGE_ASSERT( !IsFree( queue->st.w ), "Queue is already free(enqueue)" );
    sem_wait( queue->qremain );
    pthread_mutex_lock( queue->queue_lock );
    if( !(queue->head) ) queue->head = create_queue_node( value );
    else{
        queue_node_t *temp_queue_node = create_queue_node( value );
        queue->enqueue( &queue->head->list, &temp_queue_node->list );
    }
    queue->count++;
    pthread_mutex_unlock( queue->queue_lock );
    sem_post( queue->qitem );
}

void* ENQUEUE_INTF( void *queue_data_temp ){
    mul_queue_data_t *queue_data = (mul_queue_data_t *)queue_data_temp;
    mul_queue_t *queue = queue_data->queue;
    MUL_HODGEPODGE_ASSERT( IsAllocate( queue_data->queue->st.w ), "Stack not allocated.." );
    void *value = queue_data->value;
    enqueue( queue, value );
}

void dequeue( mul_queue_t **queue )
{
    mul_queue_t *q = *queue;
    MUL_HODGEPODGE_ASSERT( IsAllocate( q->st.w ), "Queue not allocated" );
    sem_wait( q->qitem );
    pthread_mutex_lock( q->queue_lock );
    list_t *temp = &(q->head->list);
    temp = q->dequeue(temp);
    q->count--;
    if( q->count == 0 ){
        q->head->st.w = 0;
        q->head->st.bit.is_free = 1;
        if( IsCreateByMalloc( q->head->st.w ) ) free(q->head);
        q->head = NULL;
    }
    else{
        q->head->list = *temp;
    }
    pthread_mutex_unlock( q->queue_lock );
    sem_post( q->qremain );
}

void free_queue( mul_queue_t **queue ) 
{
    MUL_HODGEPODGE_ASSERT( IsAllocate( (*queue)->st.w), "Queue not allocated" );
    if( !(*queue)->head ){
        free(*queue);
        *queue = NULL;
        return;
    }
    if( IsAllocate( (*queue)->st.w) && !IsFree( (*queue)->st.w) ){
        free_list( &((*queue)->head)->list );
    }
    (*queue)->head->st.bit.is_free = 1;
    (*queue)->head = NULL;
    free((*queue)->qremain);
    (*queue)->qremain = NULL;
    free((*queue)->qitem);
    (*queue)->qitem = NULL;
    free((*queue)->queue_lock);
    (*queue)->queue_lock = NULL;
    free(*queue);
    *queue = NULL;
}