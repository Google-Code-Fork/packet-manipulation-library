
#include "threads.h"
#include <stdexcept>
#include <errno.h>
Mutex::Mutex()
{
#ifndef WIN32 // UNIX
	mutex_ = new pthread_mutex_t;
	int err = pthread_mutex_init( mutex_, NULL );
	if( err )
		throw std::runtime_error( "Can not init mutex" );
#endif
}

Mutex::~Mutex()
{
	#ifndef WIN32 // UNIX
	int err = pthread_mutex_destroy( mutex_ );
	if ( err == EBUSY)
	  throw std::runtime_error( "Can not destroy mutex: Locked by other thread");
	if ( err == EINVAL )
	  throw std::runtime_error( "Mutex has invalid value and cannot be destroyed" );
	if( err )
		throw std::runtime_error( "Can not destroy mutex" );
	#endif
}

Mutex::Mutex( const Mutex& mutex )
{
	#ifndef WIN32 //UNIX
	mutex_ = new pthread_mutex_t;
	mutex_ = mutex.mutex_;
	#endif
}

void Mutex::lock()
{
	#ifndef WIN32 // UNIX
	pthread_mutex_lock( mutex_ );
	#endif
}

void Mutex::unlock()
{
	#ifndef WIN32 //UNIX
	pthread_mutex_unlock( mutex_ );
	#endif
}

int Mutex::trylock()
{
	#ifndef WIN32 //UNIX
	int val = pthread_mutex_trylock( mutex_ );
	#endif
	return val;
}
