#define DECLARE_THREAD(type,ele_1) \
        typedef struct thread_param { \
            type##_t *type;  \
            ele_1 node;     \
        }threadpa_t;
        