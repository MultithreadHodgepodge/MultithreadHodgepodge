#define MUL_HODGEPODGE_ASSERT(condition,message) \
    if(!(condition)) { \
        printf("Assert: Program stop => %s\n",message);\
        exit(0); \
    }
    