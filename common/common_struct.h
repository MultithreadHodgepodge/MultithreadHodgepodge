#define STRUCT_IS_ADDED (1<<4)
#define STRUCT_IS_FREE (1<<2)
#define STRUCT_IS_CREATED_BY_MALLOC (1<<1)
#define STRUCT_IS_ALLOCATED (1<<0)

typedef struct state_b{
    /* 0:Not configured 1:Configured*/
    uint8_t configured        :1; 
    /* The struct created by malloc 0:No 1:Yes*/
    uint8_t is_malloc         :1;
    /* The struct freed or not 0:No 1:Yes*/
    uint8_t is_free           :1;
    /* If the struct be operated by multithread 0:No 1:Yes*/
    uint8_t is_multithread    :1;
    uint8_t is_added          :1;
    uint8_t is_head           :1;
    int _reserved         :3;
}BIT_T;

typedef union __state{
    /* data */
    BIT_T bit;
    uint8_t w;
}state;

#define IsAllocate(st) (st&STRUCT_IS_ALLOCATED)
#define IsCreateByMalloc(st) (st&STRUCT_IS_CREATED_BY_MALLOC)
#define IsFree(st) (st&STRUCT_IS_FREE)
#define IsAdd(st) (st&STRUCT_IS_ADDED)