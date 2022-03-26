//TODO!!!
void create_priority_queue(priority_queue_t **queue, int qun) {
    (*queue)=(priority_queue_t*)malloc(sizeof(priority_queue_t));
    create_queue(&((*queue)->queue),qun);
}
void enqueue(threadpa_t *para){
    if (!para) {
        puts("parameter is empty\n");
        return ;
    }
    priority_queue_t *q = para->queue;
    if (!q) {
        puts("priority queue is not exist\n");
        return ;
    }
    
}

void dequeue(priority_queue_t **queue){

}



void print_queue(priority_queue_t **queue){

}

void free_queue(priority_queue_t **queue){
    
}