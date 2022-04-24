#include "../tree.h"
typedef struct __binary_tree{
    tree_t *head;
    tree_t *last;
}binary_tree_t;

void create_binary_tree(binary_tree_t **);
void insert_last(tree_t *,(void *)value);
void delete_last(tree_t *);