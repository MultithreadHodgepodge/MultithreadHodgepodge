#include<stdbool.h>
#include<stdlib.h>
typedef struct __tree tree_t;
typedef struct __tree{
    void *value;
    bool head;
    struct __tree *left;
    struct __tree *right;
    struct __tree *parent;
    void (*insert)(tree_t**, void*);
    void (*delete)(tree_t**);
    void (*printtree)(tree_t** );
    void (*freetree)(tree_t **);
}tree_t;
void create_tree(tree_t **);
void set_tree_insert(tree_t **, void (*insert)(tree_t**, void*));
