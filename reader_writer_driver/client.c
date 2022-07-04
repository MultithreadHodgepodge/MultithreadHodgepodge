#include <stdio.h>
#include <fcntl.h>

#define OBJECT_DEVICE "/dev/rwdriver"

int main() 
{
	int fd = open(OBJECT_DEVICE, O_RDWR); 
/*	
	char buf1[100] = {0};
	if(read(fd, buf1, 100)) {
		puts("No data in buffer");
	} 

	char buf2[] = {"Data is here"};
	if (write(fd, buf2, sizeof(buf2))) {
		puts("No Space for write");
	}

	char buf3[101] = {0};
	if (read(fd, buf, 100)) {
		puts("No data in buffer");
	}

	puts(buf3);	
*/
	close(fd);
	
	return 0;	
}
