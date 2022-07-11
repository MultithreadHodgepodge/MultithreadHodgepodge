#include "rwlock.h"
#include <string.h>
#include <time.h>
#include <pthread.h>

#define PTHREAD_Q 5

static void *reader(void *);
static void *writer(void *);

typedef struct thread_info {

	int tid;
	rwlock_t *rwlock;
	char *msg;

}tinfo_t;

static const char dict[][20] = { 
	"I am writer\0",
	"I am singer\0",
	"I am ranger\0",
	"I am pramgrammer\0",
};

static const int size = sizeof(dict) / (sizeof(char) * 20);

int main()
{
	srand(time(NULL));
	void *(*work[])(void *) = {
		reader, 
		writer,
	};

	/* lock and storage initialize */
	tinfo_t *tinfo = (tinfo_t *)malloc(sizeof(tinfo_t) * PTHREAD_Q);
	char *msg = (char *)malloc(sizeof(char) * 100);
	rwlock_t *lock = lock_init();
	strncpy(msg, "Initial data\0", 14);

	/* assign thread parameter */
	for (int i = 0;i < PTHREAD_Q;++i) {
		tinfo[i].msg = msg;
		tinfo[i].rwlock = lock;
		tinfo[i].tid = i;
	}

	pthread_t pid[PTHREAD_Q];
	for (int i = 0;i < PTHREAD_Q;++i) {
		pthread_create(&pid[i], NULL, work[rand() % 2], &tinfo[i]);	
	}
	for (int i = 0;i < PTHREAD_Q;++i)
		pthread_join(pid[i], NULL);

	rwlock_free(tinfo->rwlock);
	free(tinfo->msg);
	free(tinfo);

	return 0;
}

static void *reader(void *tinfo) 
{
	tinfo_t *info = (tinfo_t *)tinfo;		

	read_lock(info->rwlock);

	printf("thread %d reading: %s\n", info->tid, info->msg);

	read_unlock(info->rwlock);

}

static void *writer(void *tinfo)
{	
	tinfo_t *info = (tinfo_t *)tinfo;		

	char writer_msg[20];
	strncpy(writer_msg, dict[rand() % size], 20);
	write_lock(info->rwlock);

	strncpy(info->msg, writer_msg, 20);
	printf("thread %d writing: %s\n", info->tid, writer_msg);

	write_unlock(info->rwlock);

}

