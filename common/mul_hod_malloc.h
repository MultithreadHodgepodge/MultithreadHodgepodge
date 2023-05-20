/**
 * @brief: malloc space for list_t node
*/
#define MALLOC_LIST() \
    (list_t*)malloc(sizeof(list_t));\

/**
 * @brief: malloc space for mul_stack_t node
*/
#define MALLOC_STACK() \
    (mul_stack_t*)malloc(sizeof(mul_stack_t));\

/**
 * @brief: malloc space for stack_node_t node
*/
#define MALLOC_STACK_NODE() \
    (stack_node_t*)malloc(sizeof(stack_node_t));\

/**
 * @brief: malloc space for mul_stack_data_t node
*/
#define MALLOC_STACK_DATA() \
    (mul_stack_data_t*)malloc(sizeof(mul_stack_data_t));\

/**
 * @brief: malloc space for mul_queue_t node
*/
#define MALLOC_QUEUE() \
    (mul_queue_t*)malloc(sizeof(mul_queue_t));\

/**
 * @brief: malloc space for stack_node_t node
*/
#define MALLOC_QUEUE_NODE() \
    (queue_node_t*)malloc(sizeof(queue_node_t));\

/**
 * @brief: malloc space for mul_queue_data_t node
*/
#define MALLOC_QUEUE_DATA() \
    (mul_queue_data_t*)malloc(sizeof(mul_queue_data_t));\
