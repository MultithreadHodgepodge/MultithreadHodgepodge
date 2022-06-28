#include "threadpool.h"

/*
 * @front : ringbuffer's start index
 * @end   : ringbuffer's tail index
 * @item  : how many function in this ringbuffer semaphore counter
 * @remain: how many space in this ringbuffer semaphore counter
 * @mutex : critical section control for take jobs and add jobs
 * @ringbuffer: it will calloc a circular queue for containing jobs
 * @rq    : threadpool's pointer, for accessing ringbuffer
 */
void readyqueue_init(RQ_t **rq)
{
	int front, end;
	sem_t item, remain;
	pthread_mutex_t mutex;
	void *ringbuffer;

	*rq = (RQ_t *)malloc(sizeof(RQ_t));
	(*rq)->ringbuffer = calloc(rq_capacity, sizeof(void *));
	(*rq)->front = (*rq)->end = 0;
	sem_init(&(*rq)->item, 0, 0);
	sem_init(&(*rq)->remain, 0, rq_capacity);
	pthread_mutex_init(&(*rq)->mutex, NULL);
	
	sigready_queue = *rq;
}

/* @rq: threadpool's ringbuffer 
 * @t : contain job assgning to thread
 */

void* task(RQ_t *rq)
{
	

	if (rq == NULL) {
		puts("rq is empty");
		exit(3);
	}

	void* t;
	sem_wait(&rq->item);

	if (!finish)
		return NULL;

	pthread_mutex_lock(&rq->mutex);	

	t = rq->ringbuffer[rq->end];
	rq->ringbuffer[rq->end] = NULL;
	rq->end = (rq->end + 1) % rq_capacity;
	
	pthread_mutex_unlock(&rq->mutex);
	sem_post(&rq->remain);
	
	return t;
}

/* @rq :threadpool's ringbuffer
 * @num: choose which jobs selected
 */

void add_task(RQ_t **rq, int num)
{
	sem_wait(&(*rq)->remain);
	pthread_mutex_lock(&(*rq)->mutex);
	if ((*rq)->ringbuffer[(*rq)->front] == NULL) {
		(*rq)->ringbuffer[(*rq)->front] = select_job(num);
		(*rq)->front = ((*rq)->front + 1) % rq_capacity;
	} else {
		puts("Ringbuffer is full");
	}
	pthread_mutex_unlock(&(*rq)->mutex);
	sem_post(&(*rq)->item);
}

/* @num: decide which jobs is selected 
 */

void* select_job(int num)
{

	void (*factory[])() = {foo1, foo2, foo3};
	if (num < 3)
		return factory[num];
	else
		return  factory[0];
}	

/* @tinfo: contain thread information: tid, thread worker id, jobs pointer ....
 * @rq   : threadpool's ringbuffer, make worker thread to know the address of readyqueue 
 */

void threadpool_init(TINFO_t **tinfo, RQ_t **rq)
{
	*tinfo = (TINFO_t *)malloc(sizeof(TINFO_t) * threadQ);

	for (int i = 0;i < threadQ;i++) {
		(*tinfo)[i].thread_num = i;
		(*tinfo)[i].rq = (*rq);
		if (pthread_create(&(*tinfo)[i].thread_id, NULL, worker, &(*tinfo)[i])) {	
			perror("pthread_create: Wrong create");
			exit(2);
		} else {
			printf("%d ", (*tinfo)[i].thread_num);
			puts("init sucess");
		}
	}
}

/* @rq   : threadpool's ringbuffer
 * @tinfo: contain current thread information 
 */

void close_threadpool(RQ_t **rq, TINFO_t **tinfo)
{
	void *ret = 0;
	for (int i = 0;i < threadQ;++i, ret = 0)
		pthread_join((*tinfo)[i].thread_id, &ret);

	free(*tinfo);
	free((*rq)->ringbuffer);
	free(*rq);
}

/* @arg: pthread_create's argument
 */

void *worker(void *arg)
{
	
	RQ_t *rq = ((TINFO_t *)arg)->rq;
	if (rq == NULL) {
		puts("worker: rq is NULL");
		exit(4);
	}

	void* t;
	while(finish) {
		t = task(rq);
		
		if (t == NULL)
			break;
		((targetfun)t)();
	}
	return t;
}

/* @num: tell which asychronize interrupt happend 
 */

void interrupt(int num)
{
	if (num == SIGINT) {
		int n;
		char *jd;
		char c[10] = {0};
		char *sptr = NULL;
		while(c[0] != 'c' && c[0] != 'C') {
			printf("\nshell -> ");
			fgets(c, 10, stdin);
			switch(c[0]) {
			case 'c':
			case 'C':
				break;

			case 'a':
			case 'A':
				jd = strtok_r(c, " ", &sptr);
				while(jd = strtok_r(NULL, " ", &sptr)) {
					if (n = atoi(jd)) {
						add_task(&sigready_queue, n);
						printf("task: %d\n", n);
					}
				}
				break;
			case 'e':
			case 'E':
				finish = 0;
				for (int i = 0;i < threadQ;++i)
					sem_post(&sigready_queue->item);
				c[0] = 'c';
				perror("exit ");
				break;
			default:
				break;
			}
		}
	}
}

/* @foo1: mock function
 * @foo2: mock function
 * @foo3: mock function
 */

void foo1()
{
	int c = t;
	while (c--)
		puts("this is foo1");
}

void foo2()
{
	int c = t;
	while (c--)
		puts("    this is foo2");
}

void foo3()
{
	int c = t;
	while (c--)
		puts("        this is foo3");
}
