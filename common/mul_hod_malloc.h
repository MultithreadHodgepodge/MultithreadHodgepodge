/**
 * @brief: malloc space for list_t node
*/
#define MALLOC_LIST() \
    (list_t*)malloc(sizeof(list_t));\

/**
 * @brief: malloc space for mul_xxx_t
 * @struct_name: name of xxx
*/
#define MALLOC_MUL_T(struct_name)  \
    ( mul_ ## struct_name ## _t *)malloc(sizeof( mul_ ## struct_name ## _t ));

/**
 * @brief: malloc space for xxx_node_t node
*/
#define MALLOC_NODE_T(node_name)  \
    ( node_name ## _node_t *)malloc(sizeof( node_name ## _node_t ));
