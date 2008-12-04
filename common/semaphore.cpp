

#include "threads.h"

Semaphore::Semaphore( int num ):num_(num)
{
	pthread_mutex_init( &count_mutex, NULL );
	pthread_cond_init( &count_condition, NULL );
	if( num_ > 0 )
	{
		pthread_cond_signal(&count_condition);
	}
}

void Semaphore::post()
{
	pthread_mutex_lock( &count_mutex );
	++num_;
	pthread_cond_signal( &count_condition );
	pthread_mutex_unlock( &count_mutex );
}

void Semaphore::wait()
{
	pthread_mutex_lock( &count_mutex );
	if( num_ == 0 )
	{
		pthread_cond_wait( &count_condition, &count_mutex );
	}
		--num_;
	pthread_mutex_unlock( &count_mutex );
}

int Semaphore::getNum()
{
	pthread_mutex_lock( &count_mutex );
	int tmp = num_;
	pthread_mutex_unlock( &count_mutex );
	return tmp;
}
