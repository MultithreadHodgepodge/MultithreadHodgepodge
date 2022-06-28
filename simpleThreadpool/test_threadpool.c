#include "threadpool.h"

int main()
{	
	signal(SIGINT, interrupt);
	TINFO_t *tinfo;
	RQ_t *rq;
	readyqueue_init(&rq);
	threadpool_init(&tinfo, &rq);
	
	for (int i = 0;i < rq_capacity + 10;++i) {
		add_task(&rq, i % 3);
	}

	//show(&rq);

	close_threadpool(&rq,&tinfo);
	puts("\n----------finished----------");
}