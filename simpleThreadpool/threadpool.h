#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>


static const int threadQ = 4;
static const int t = 5;
static const int rq_capacity = 20;

typedef void (*targetfun)();
typedef struct Readyqueue {	
	
	int front, end;
	sem_t item, remain;
	pthread_mutex_t mutex;
	targetfun *ringbuffer;
	

}RQ_t;


typedef struct thread_info {
	pthread_t thread_id;
	int thread_num;
	char *argv_string;	
	RQ_t *rq;

}TINFO_t;

void threadpool_init(TINFO_t **, RQ_t **);
void readyqueue_init(RQ_t **);
void foo1();
void foo2();
void foo3();
void *worker(void *);
void interrupt(int );
void close_threadpool(RQ_t **,TINFO_t **);
void add_task(RQ_t **, int );
void show(RQ_t **);
void* task(RQ_t *);
RQ_t *sigready_queue;
void* select_job(int );

static int finish = 1;

