#include <stdio.h>
#include "threadpool.h"

int main()
{
    pthread_t t[3];
    create_threadpool(3);
    return 0;
}