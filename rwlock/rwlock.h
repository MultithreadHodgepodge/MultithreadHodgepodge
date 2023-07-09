#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct rwlock {
	
	int reading;
	int writing;

	/* if writer comes, 
	 * it represent coming reader should wait writer 
	 */
	int write;	
	pthread_cond_t cv;
	pthread_mutex_t mt;

} rwlock_t;

rwlock_t *lock_init();
void read_lock( rwlock_t * );
void read_unlock( rwlock_t * );
void write_lock( rwlock_t * );
void write_unlock( rwlock_t * );
void rwlock_free( rwlock_t * );


