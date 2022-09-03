#include <stdio.h>
#include "minheap.h"

#define N 11
#define THREAD_NUM 10

typedef struct thread_arg 
{
	minHeap_t *heap;
	int val;
	int result;

}th_arg_t;

typedef void *(*func)(void *);

func heap_action[] = {
	heap_pop_wrapper,
	heap_push_wrapper,
};


int main()
{
	minHeap_t *heap = NULL;
	/* test no heap */
	printf("minHeapPop: %d\n", minHeapPop(heap));

/*
	int minHeapPop(minHeap_t *);
	int  minHeapPush(minHeap_t *, int );
*/
	pthread_t tid[THREAD_NUM];
	heap = createMinHeap(N);
	th_arg_t arg[THREAD_NUM];

	for (int i = 0;i < THREAD_NUM;++i) {
		arg[i].heap = heap;
		arg[i].val = i;
		pthread_create(&tid[i], NULL, heap_action[1], &arg[i]);
	}

	for (int i = 0;i < THREAD_NUM;++i) {
		pthread_join(tid[i], NULL);
		printf("push: %d\n", arg[i].result);
	}

	for (int i = 0;i < THREAD_NUM;++i) 
		printf("%d ", heap->minheap[i]);


	for (int i = 0;i < THREAD_NUM;++i) {
		arg[i].heap = heap;
		arg[i].val = i;
		pthread_create(&tid[i], NULL, heap_action[0], &arg[i]);
	}

	for (int i = 0;i < THREAD_NUM;++i) {
		pthread_join(tid[i], NULL);
		printf("pop: %d\n", arg[i].result);
	}
	puts("");
}

void *heap_pop_wrapper(void *argument)
{
	th_arg_t *arg = (th_arg_t *)argument;
	arg->result = minHeapPop(arg->heap);
	pthread_exit(NULL);
}

void *heap_push_wrapper(void *argument)
{
	th_arg_t *arg = (th_arg_t *)argument;
	arg->result = minHeapPush(arg->heap, arg->val);
	pthread_exit(NULL);
}

