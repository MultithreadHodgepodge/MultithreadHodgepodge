#include "threadpool.h"

/** 
 * readyqueue_init()- Initialize RQ_T
 * @rq: Pointer to pointer RQ_t
 * @rq_capacity: Size of RQ
 * @threadQ: Thread number operating on RQ
 */
void readyqueue_init(RQ_t **rq,int rq_capacity, int threadQ)
{
	int front, end;
	sem_t item, remain;
	pthread_mutex_t mutex;
	//void *ringbuffer;
	*rq = (RQ_t *)malloc(sizeof(RQ_t));
	if (*rq == NULL) {
		perror("rq_init: ");
		exit(errno);
	}

	/* judge is 2^x or not */
	if (rq_capacity & (rq_capacity - 1)) {
		/* padding to 2^x */
		int c = 1;
		while(rq_capacity >>= 1)c++;
		rq_capacity = 1<<c;
	}

	(*rq)->front = (*rq)->end = 0;
	sem_init(&(*rq)->item, 0, 0);
	sem_init(&(*rq)->remain, 0, rq_capacity);
	pthread_mutex_init(&(*rq)->mutex, NULL);
	(*rq)->rq_capacity=rq_capacity;
	(*rq)->threadQ=threadQ;
	(*rq)->task_rq=(task_list *)malloc(sizeof(task_list));
	(*rq)->task_rq=NULL;
	sigready_queue = *rq;

	return;	

ringbuffer_fail:

	free(*rq);
	exit(errno);

}
/** take_task()- Get task from RQ 
 * @rq: Pointer to RQ_t
 */
void* take_task(RQ_t *rq)
{
	if (rq == NULL) {
		puts("rq is NULL");
		exit(3);
	}

	void (*t)();
	t = NULL;

	sem_wait(&rq->item);

	if (!finish)
		return NULL;

	pthread_mutex_lock(&rq->mutex);	
	

	t=rq->task_rq->task_func;
	task_list *temp=rq->task_rq;
	rq->task_rq=list_entry((rq->task_rq->list.next),task_list ,list);

	pthread_mutex_unlock(&rq->mutex);
	sem_post(&rq->remain);

	return t;
}
/** 
 * create_task_list()-@rq :Create new task_list
 * @rq: Pointer to pointer to task_list
 */
void create_task_list(task_list **task){
	*task=(task_list*)malloc(sizeof(task_list));
	
	list_t *head = &(*task)->list;
	CONNECT_SELF(head)
	(*task)->task_func=NULL;
}
/** 
 * add_task_list()-@rq :Add task into RQ
 * @rq: Pointer to pointer to RQ_t
 * @new_task: Pointer to task_list 
 */
void add_task_list(RQ_t **rq,task_list *new_task){
	//Check if task_rq is empty
	if((*rq)->task_rq==NULL)
	{
		(*rq)->task_rq=new_task; 
		return;
	}
	list_add_tail((&(*rq)->task_rq->list),&new_task->list);

}
/** 
 * add_task()-Add task into RQ
 * @rq: Pointer to RQ_t
 * @num: choose which jobs selected
 */
void add_task(RQ_t *rq, int num)
{
	sem_wait(&rq->remain);
	pthread_mutex_lock(&rq->mutex);
	task_list *new_task;
	create_task_list(&new_task);
	new_task->task_func=select_job(num);
	add_task_list(&rq,new_task);
	pthread_mutex_unlock(&rq->mutex);
	sem_post(&rq->item);
}

/** set_job()-Set job list 
* @task: Function pointer to be assigned  
* @index: The index of the function in function pointer list factory
*/
void set_job(void (*task)(),int index){
	factory[index]=task;
}

/** select_job()-Select Task 
* @num: decide which jobs is selected 
*/
void* select_job(int num)
{
	if (num < 3)
		return factory[num];
	else
		return  factory[0];
}	

/** threadpool_init()- Initialize threadpool
 * @tinfo: contain thread information: tid, thread worker id, jobs pointer ....
 * @rq: Pointer to pointer to RQ_t make worker thread to know the address of readyqueue 
 * @threadQ: Thread number
 */
void threadpool_init(TINFO_t **tinfo, RQ_t **rq,int threadQ)
{
	*tinfo = (TINFO_t *)malloc(sizeof(TINFO_t) * threadQ);
	if (*tinfo == NULL) {
		perror("threadpool_init: ");
		return ;
	}

	int i;
	for (i = 0;i < threadQ;i++) {
		(*tinfo)[i].thread_num = i;
		(*tinfo)[i].rq = (*rq);
		if (pthread_create(&(*tinfo)[i].thread_id, NULL, worker, &(*tinfo)[i])) {	
			perror("pthread_create: ");
			goto fail;
		} else {
			printf("%d ", (*tinfo)[i].thread_num);
		}
	}


	return ;
fail:
	while(--i < 0) {
		pthread_join((*tinfo)[i].thread_id, NULL);
	}
	free(*tinfo);
	exit(2);
}

/** close_threadpool()-Close RQ 
 * @rq   : threadpool's ringbuffer
 * @tinfo: contain current thread information 
 */
void close_threadpool(RQ_t **rq, TINFO_t **tinfo, int threadQ)
{
	void *ret = 0;
	for (int i = 0;i < threadQ;++i, ret = 0)
		pthread_join((*tinfo)[i].thread_id, &ret);

	free(*tinfo);
	free((*rq)->task_rq);
	free(*rq);
}

/** worker()- Take task to execute
* @arg: pthread_create's argument
*/
void *worker(void *arg)
{

	RQ_t *rq = ((TINFO_t *)arg)->rq;
	if (rq == NULL) {
		puts("worker: rq is NULL");
		exit(4);
	}

	void (*t)();
	t = foo1;
	while(finish) {

		t = take_task(rq);

		if (t == NULL){
			
			break;
		}
		t();
	}
	return t;
}

/** interrupt()-Tell process do what
* @num: tell which asychronize interrupt happend 
*/
void interrupt(int num)
{
	if (num == SIGINT) {
		int n;
		char *jd;
		char c[100] = {0};
		char *sptr = NULL;
		while(c[0] != 'c' && c[0] != 'C') {
			printf("\nshell -> ");
			fgets(c, 100, stdin);

			if(!strcmp(c, "help\n")) {
				puts("		C/c: threadpool continue");
				puts("		A/a: add task into threadpool");
				puts("		E/e: cloes threadpool");
			}
			else {
				switch(c[0]) {
					case 'c':
					case 'C':
						break;

					case 'a':
					case 'A':
						jd = strtok_r(c, " ", &sptr);
						while(jd = strtok_r(NULL, " ", &sptr)) {
							if (n = atoi(jd)) {
								add_task(sigready_queue, n-1);
							}
						}
						break;
					case 'e':
					case 'E':
					case 'q':
					case 'Q':
						finish = 0;
						for (int i = 0;i < sigready_queue->threadQ;++i)
							sem_post(&sigready_queue->item);
						c[0] = 'c';
						perror("exit ");
						break;
					default:
						printf("unknown command, check <help> to fetch more information");
						break;
				}
			}
		}
	}
}

void foo1()
{
	int c = 5;
	while (c--)
		puts("this is foo1");
}

void foo2()
{
	int c = 5;
	while (c--)
		puts("    this is foo2");
}

void foo3()
{
	int c = 5;
	while (c--)
		puts("        this is foo3");
}
