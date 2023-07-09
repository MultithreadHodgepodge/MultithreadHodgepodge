#include "rwlock.h"

rwlock_t *lock_init()
{
	/* create lock in heap section */
	rwlock_t *lock = (rwlock_t *)malloc( sizeof(rwlock_t) );
	lock->reading = lock->writing = lock->write = 0;
	pthread_mutex_init( &lock->mt, NULL );

	/* cv initialize */
	pthread_condattr_t cattr;
	pthread_condattr_init( &cattr );
	pthread_cond_init( &lock->cv, &cattr );

	return lock;
}

void read_lock( rwlock_t *lock )
{
	pthread_mutex_lock( &lock->mt );

	/* if writer or writer is line up, 
	 * comming reader sleep until writer finishing it's work
	 */
	while( lock->writing || lock->write ) {
		pthread_cond_wait( &lock->cv, &lock->mt );
	}

	/* reader enter cs, reader counter increase */
	lock->reading++;
	pthread_mutex_unlock( &lock->mt );
}

void read_unlock( rwlock_t *lock )
{
	pthread_mutex_lock( &lock->mt );
	/* decrese reader's quntitiy in cs */
	lock->reading--;

	/* wake writer up, if this is the last one reader */
	if ( lock->reading == 0 )
		pthread_cond_broadcast( &lock->cv );
	
	pthread_mutex_unlock( &lock->mt );
}

void write_lock( rwlock_t *lock )
{
	pthread_mutex_lock( &lock->mt );
	/* writer is lining up */
	lock->write++;
	/* if there are readers or writer in cs, sleep until they leave */
	while ( lock->reading || lock->writing ) {
		pthread_cond_wait( &lock->cv, &lock->mt );
	}
	/* writer is leaving line and enter cs */
	lock->write--;
	lock->writing++;
	pthread_mutex_unlock( &lock->mt );
}

void write_unlock( rwlock_t *lock )
{
	pthread_mutex_lock( &lock->mt );
	/* writer is leaving cs, writing decrease */
	lock->writing--;

	/* if there is writer in the line */
	pthread_cond_broadcast( &lock->cv );

	pthread_mutex_unlock( &lock->mt );
}

void rwlock_free( rwlock_t *lock )
{	
	free(lock);
	return ;
}
