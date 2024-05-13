#include <stdio.h>
#include "../list/list.h"
#include "../list/stack/stack.h"
#include "../list/queue/queue.h"
//Reference https://github.com/clibs/bench for benchmarking
#include "../bench/bench.h"

static int nodes=1000000;

void speedtest_list(){
    puts( "=======Start test list_add_head========\n" );
    list_t *list = create_list( list );
    float start = cpu();
    while ( nodes-- )
    {
        list_t *node1 = create_list( NULL );
        list_add_head( &list, node1 );
    }

    float dur = cpu()-start;
    printf( "=======End test list_add_head duration is %.3f ms========\n", dur );
    puts( "\n=======Start test list_remove_head========\n" );
    start = cpu();
    while ( list != NULL )
    {
        list = list_remove_head( list );
    }
    dur = cpu()-start;
    printf("=======End test list_remove_head duration is %.3f ms========\n", dur);

    puts( "\n=======Start test list_add_tail========\n" );
    nodes = 1000000;
    list = create_list(list);
    start = cpu();
    while ( nodes-- )
    {
        list_t *node1 = create_list( NULL );
        list_add_tail( list, node1 );
    }

    dur = cpu()-start;
    printf( "=======End test list_add_tail duration is %.3f ms========\n", dur );
    puts( "\n=======Start test list_remove_tail========\n" );
    start = cpu();
    while ( list != NULL && list->st.w != 0 )
    {
        list_remove_tail( list );
    }

    dur = cpu()-start;
    printf( "=======End test list_remove_tail duration is %.3f ms========\n", dur );
}

void speedtest_stack(){
    puts("=======Start test mulstack:push()========\n");
    mul_stack_t *stack=NULL;
    stack=create_stack(stack,1000000);
    int i;
    float start=cpu();
    for(i=0;i<1000000;i++){
        mul_stack_data_t *data1=pack_stack_data(stack,(void *)i);
        push(data1);
    }
    float dur=cpu()-start;
    printf("=======End test mulstack:push() duration is %.3f ms========\n", dur);
    puts("\n=======Start test mulstack:pop()========\n");
    start=cpu();
    while(stack->count){
        pop(stack);
    }
    dur=cpu()-start;
    printf("=======End test mulstack:pop() duration is %.3f ms========\n", dur);
}

void speedtest_queue(){
    puts("=======Start test mulqueue:enqueue()========\n");
    mul_queue_t *queue=NULL;
    queue=create_queue(queue,1000000);
    int i;
    float start=cpu();
    for(i=0;i<1000000;i++){
        mul_queue_data_t *data1=pack_queue_data(queue,(void *)i);
        enqueue(data1);
    }
    float dur=cpu()-start;
    printf("=======End test mulqueue:push() duration is %.3f ms========\n", dur);
    puts("\n=======Start test mulstack:pop()========\n");
    start=cpu();
    while(queue->count){
        dequeue(&queue);
    }
    dur=cpu()-start;
    printf("=======End test mulqueue:dequeue() duration is %.3f ms========\n", dur);
}
int main(){
    puts("!!!!!!!!!!!!!!!!! Test LIST SPEED !!!!!!!!!!!!!!!!");
    speedtest_list();
    puts("!!!!!!!!!!!!!!!!! Test STACK SPEED!!!!!!!!!!!!!!!!");
    speedtest_stack();
    puts("!!!!!!!!!!!!!!!!! Test QUEUE SPEED!!!!!!!!!!!!!!!!");
    speedtest_queue();
    return 0;
}