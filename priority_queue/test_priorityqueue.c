#include"priority_queue.h"
#include"../common/threadpa_macro.h"
int main()
{
    priority_queue_t *priority_queue=NULL;
    create_priority_queue(&priority_queue,10);
    THREADPA_INIT(param1,priority_queue,1)
    THREADPA_INIT(param2,priority_queue,3)
    THREADPA_INIT(param3,priority_queue,2)
    enqueue(&param1);
    enqueue(&param2);
    enqueue(&param3);
    print_queue(&priority_queue);
}