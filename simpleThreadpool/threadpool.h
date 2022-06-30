#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>

/*
 * Info about readyqueue 
 * @rq_capacity: ringbuffer's maximum element
 * @threadQ : number of threads access the ringbuffer
 * @front : ringbuffer's start index
 * @end   : ringbuffer's tail index
 * @item  : how many function in this ringbuffer semaphore counter
 * @remain: how many space in this ringbuffer semaphore counter
 * @mutex : critical section control for take jobs and add jobs
 * @ringbuffer: it will calloc a circular queue for containing jobs(Pointer to pointer)
 */
typedef struct Readyqueue {	
	int rq_capacity;
	int threadQ;
	int front, end;
	sem_t item, remain;
	pthread_mutex_t mutex;
	void (**ringbuffer)();
	

}RQ_t;

/*
 * Info about each thread
 * @thread_id: Id of thread
 * @thread_num : The order number of thread
 * @argv_string: Argument
 * @rq: ReadyQueue the thread access
 */
typedef struct thread_info {
	pthread_t thread_id;
	int thread_num;
	char *argv_string;	
	RQ_t *rq;
}TINFO_t;

void threadpool_init(TINFO_t **, RQ_t **,int );
void readyqueue_init(RQ_t **,int ,int );
void foo1();
void foo2();
void foo3();
void *worker(void *);
void interrupt(int );
void close_threadpool(RQ_t **,TINFO_t **,int);
void add_task(RQ_t **, int );
void show(RQ_t **);
void* task(RQ_t *);
RQ_t *sigready_queue;
void* select_job(int );

static int finish = 1;

