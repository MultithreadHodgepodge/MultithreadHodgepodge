#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#endif


struct minheap {
	int *minheap;
	int capacity;
	int size;
	pthread_mutex_t lock;
	pthread_cond_t full;
	pthread_cond_t empty;
};

typedef struct minheap minHeap_t;

minHeap_t *createMinHeap(int );
int minHeapPop(minHeap_t *);
int  minHeapPush(minHeap_t *, int );
void *heap_pop_wrapper(void *arg);
void *heap_push_wrapper(void *arg);
void swap(int *, int *);
