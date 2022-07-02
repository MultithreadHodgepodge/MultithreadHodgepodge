#include "threadpool.h"

int main()
{	
	signal(SIGINT, interrupt);
	TINFO_t *tinfo;
	RQ_t *rq;
	int rq_capacity=20;
	int threadQ=4;
	readyqueue_init(&rq,rq_capacity,threadQ);
	threadpool_init(&tinfo, &rq,threadQ);
	
	for (int i = 0;i < rq_capacity + 10;++i) {
		add_task(rq, i % 3);
	}

	//show(&rq);

	close_threadpool(&rq,&tinfo,threadQ);
	puts("\n----------finished----------");
}
