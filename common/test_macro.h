#define DECLARE_THREAD(type) \
        typedef struct thread_param { \
            type##_t *type;  \
            list_t *node;     \
        }threadpa_t;
        