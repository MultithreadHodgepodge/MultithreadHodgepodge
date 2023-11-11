#define typename(x) _Generic((x),                                                 \
            _Bool: "%d",                  unsigned char: "unsigned char",          \
             char: "%c",                     signed char: "signed char",            \
        short int: "short int",         unsigned short int: "unsigned short int",     \
              int: "%d",                     unsigned int: "unsigned int",           \
         long int: "long int",           unsigned long int: "unsigned long int",      \
    long long int: "long long int", unsigned long long int: "unsigned long long int", \
            float: "%f",                         double: "double",                 \
      long double: "long double",                   char *: "pointer to char",        \
           void *: "pointer to void",                int *: "pointer to int",         \
          default: "other")

#define MUL_HODGEPODGE_ASSERT(condition,message) \
    if(!(condition)) { \
        printf("Assert: Program stop => %s\n",message);\
        exit(0); \
    }
    
#define MUL_HODGEPODGE_ASSERT_PARA(condition,message, parameter) \
    if(!(condition)) { \
        printf("Assert: Program stop => %s, Parameter is as below: ",message);\
        printf(typename(parameter),parameter);\
        exit(0); \
    }