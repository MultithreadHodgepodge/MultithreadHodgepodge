#define STRUCT_IS_CREATED_BY_MALLOC (1<<1)
#define STRUCT_IS_ALLOCATED (1<<0)

typedef struct state_b{
    /* 0:Not configured 1:Configured*/
    int configured        :1; 
    /* The struct created by malloc 0:No 1:Yes*/
    int is_malloc         :1;
    /* The struct freed or not 0:No 1:Yes*/
    int is_free           :1;
    /* If the struct be operated by multithread 0:No 1:Yes*/
    int is_multithread    :1;
    int _reserved         :4;
}BIT_T;

typedef union __state{
    /* data */
    BIT_T bit;
    uint8_t w;
}state;
