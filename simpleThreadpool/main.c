#include "main.h"


int main()
{	
	signal(SIGINT, interrupt);
	TINFO_t *tinfo;
	RQ_t *rq;
	readyqueue_init(&rq);
	threadpool_init(&tinfo, &rq);
	
	for (int i = 0;i < rq_capacity + 10;++i) {
		add_task(&rq, i % 3 + 1);
	}

	//show(&rq);

	close_threadpool(&tinfo);
	puts("\n----------finished----------");
}

void readyqueue_init(RQ_t **rq)
{
	int front, end;
	sem_t item, remain;
	pthread_mutex_t mutex;
	targetfun *ringbuffer;

	*rq = (RQ_t *)malloc(sizeof(RQ_t));
	(*rq)->ringbuffer = (targetfun *)calloc(rq_capacity, sizeof(targetfun));
	(*rq)->front = (*rq)->end = 0;
	sem_init(&(*rq)->item, 0, 0);
	sem_init(&(*rq)->remain, 0, rq_capacity);
	pthread_mutex_init(&(*rq)->mutex, NULL);
	
	sigready_queue = *rq;
}


targetfun task(RQ_t *rq)
{
	

	if (rq == NULL) {
		puts("rq is empty");
		exit(3);
	}

	targetfun t;
	sem_wait(&rq->item);

	if (!finish)
		return NULL;

	pthread_mutex_lock(&rq->mutex);	

	t  = rq->ringbuffer[rq->end];
	rq->ringbuffer[rq->end] = NULL;
	rq->end = (rq->end + 1) % rq_capacity;
	
	pthread_mutex_unlock(&rq->mutex);
	sem_post(&rq->remain);
	
	return t;
}

void show(RQ_t **rq)
{
	while ((*rq)->ringbuffer[(*rq)->end] != NULL) {
		(*rq)->ringbuffer[(*rq)->end]();
		(*rq)->ringbuffer[(*rq)->end] = NULL;
		(*rq)->end = ((*rq)->end + 1) % rq_capacity;
	}
}

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

targetfun select_job(int num)
{
	switch(num) {
		case 1:
			return foo1;
		case 2:
			return foo2;
		case 3:
			return foo3;
		default:
			return foo1;
	}
}	

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

void close_threadpool(TINFO_t **tinfo)
{
	void *ret = 0;
	for (int i = 0;i < threadQ;++i, ret = 0)
		pthread_join((*tinfo)[i].thread_id, &ret);

	free(*tinfo);
}

void *worker(void *arg)
{
	//printf("%d: hi\n", ((TINFO_t *)arg)->thread_num);
	
	RQ_t *rq = ((TINFO_t *)arg)->rq;
	if (rq == NULL) {
		puts("worker: rq is NULL");
		exit(4);
	}

	targetfun t;
	while(finish) {
		t = task(rq);
		
		if (t == NULL)
			break;
		t();
	}
	
}

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
				break;
			default:
				break;
			}
		}
	}
}

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
