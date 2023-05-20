#include "minheap.h"

minHeap_t *createMinHeap(int size)
{
	minHeap_t *heap = (minHeap_t *)malloc(sizeof(minHeap_t));
	heap->minheap = (int *)malloc(sizeof(int) * size);
	heap->capacity = size;
	heap->size = 0;	
	pthread_mutex_init(&heap->lock, NULL);
	pthread_condattr_t cattr;
	pthread_cond_init(&heap->full, &cattr);
	pthread_cond_init(&heap->empty, &cattr);
	return heap;
}

int minHeapPop(minHeap_t *heap)
{
	if (!heap) { 
		puts("heap is not allocate");
		return -1;
	}
	pthread_mutex_lock(&heap->lock);
	while (heap->size < 1) {
		puts("minHeapPop: minheap is empty!");
		pthread_cond_wait(&heap->empty, &heap->lock);
	}
	int val = heap->minheap[1];
	heap->minheap[1] = heap->minheap[heap->size--];
	int cur = 1;
	while (1) {
		if (2 * cur <= heap->size && 2 * cur + 1 <= heap->size && 
				(heap->minheap[cur] > heap->minheap[2 * cur] || heap->minheap[cur] > heap->minheap[2 * cur + 1])) {
			if (heap->minheap[2 * cur] < heap->minheap[2 * cur + 1]) {
				swap(&heap->minheap[2 * cur], &heap->minheap[cur]);
				cur *= 2;
			} else {
				swap(&heap->minheap[2 * cur + 1], &heap->minheap[cur]);
				cur = 2 * cur + 1;
			}
			continue;
		} else if (2 * cur <= heap->size && heap->minheap[cur] > heap->minheap[2 * cur]) {
			swap(&heap->minheap[2 * cur], &heap->minheap[cur]);
			cur *= 2;
			continue;
		}
		break;
	}
	pthread_mutex_unlock(&heap->lock);
	pthread_cond_signal(&heap->full);
	return val;
}

int minHeapPush(minHeap_t *heap, int val)
{
	if (!heap) {
		puts("heap is not allocate");
		return -1;
	}
	pthread_mutex_lock(&heap->lock);
	while (heap->size == heap->capacity) {
		puts("minHeapPush: heap capacity is full!");
		pthread_cond_wait(&heap->full, &heap->lock);
	}
	heap->minheap[++heap->size] = val;
	int cur = heap->size;
	while (1) {
		if (cur / 2 > 1 && heap->minheap[cur] < heap->minheap[cur / 2]) {
			swap(&heap->minheap[cur], &heap->minheap[cur / 2]);
			cur /= 2;
			continue;
		} 
		break;
	}
	pthread_mutex_unlock(&heap->lock);
	pthread_cond_signal(&heap->empty);
	return 0;
}

int freeHeap(minHeap_t *heap)
{
	if (!heap) {
		puts("deallocate already");
		return -1;
	}
	free(heap->minheap);
	free(heap);
	return 0;
}

void swap(int *a, int *b)
{
	if (*a == *b) {
		int t = *a;
		*a = *b;
		*b = t;
	}
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
