#include "threadpool.h"
#include <stdlib.h>
int create_threadpool(int qun)
{
    
    // if (sizeof(arr) / sizeof(pthread_t) != qun) {
    //     puts("Not corrent dercriptors of pthread number");
    //     return -1;
    // }
    int i;
    pthread_t *t = (int *)malloc(qun * sizeof(pthread_t));
    int *id = (int *)malloc(qun * sizeof(int));

    for (i = 0;i < qun;++i) {
        id[i] = i;
        pthread_create((t+i), NULL, (void *)mockTask, id+ i);
    }

    for (i = 0;i < qun;++i) {
        pthread_join(t[i], NULL);
    }
    free(id);
    free(t);
}


void mockTask(int *num)
{
    while (1) {
        printf("Hello World %d\n", *num);
    }
}