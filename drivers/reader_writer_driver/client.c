#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define OBJECT_DEVICE "/dev/rwdriver"

void *read_work(void *);
void *write_work(void *);
void *select_jobs();

void *(*work[2])(void *) = {
	read_work,
	write_work,	
};

int main(void ) 
{
	int fd = open(OBJECT_DEVICE, O_RDWR); 
	srand(time(NULL));	
	pthread_t id[5];
	
	int th_quntity = rand() % 5 + 1;
	
	write_work(&fd);

	for(int i = 0;i < th_quntity;i++)
		pthread_create(&id[i], NULL, select_jobs(), &fd);


	for (int i = 0;i < th_quntity;i++)
		pthread_join(id[i], NULL);

	read_work(&fd);

	close(fd);
	
	return 0;	
}

void *select_jobs()
{
	return work[rand() & 1];
}

void *read_work(void *arg) 
{
	int fd = *(int *)arg;
	char buf[100] = {0};
	if(read(fd, buf, 100)) {
		puts("No data in buffer");
	} 
	if (buf[0])
		puts(buf);
}


void *write_work(void *arg) 
{
	int fd = *(int *)arg;
	char buf[] = {"Data is here"};
	if (write(fd, buf, sizeof(buf))) {
		puts("No Space for write");
	}
}
