#define DECLARE_THREAD(type) \
        typedef struct thread_param { \
            type##_t *type;  \
            void *value;     \
        }threadpa_t;