
#include "threads.h"
#include <stdexcept>
#ifndef WIN32 // UNIX
#include <signal.h>
#endif

Thread::Thread( )
{
	#ifndef WIN32 //UNIX
	threadID_ = new pthread_t;
	#endif
}

Thread::Thread( StartRoutine routine ):startRoutine_(routine)
{
	#ifndef WIN32 //UNIX
	threadID_ = new pthread_t;
	#endif
}

void Thread::setStartRoutine( StartRoutine routine)
{
	startRoutine_ = routine;
}

Thread::~Thread( )
{
	delete threadID_;
}

Thread::Thread( const Thread & thread )
{
	#ifndef WIN32 //UNIX
	if( threadID_ == NULL )
		threadID_ = new pthread_t;
	startRoutine_ = thread.startRoutine_;
	threadID_ = thread.threadID_;
	#endif
}

void Thread::start( void * dataForThread )
{
	#ifndef WIN32 // UNIX
	int err = pthread_create( threadID_, NULL, startRoutine_, dataForThread );
	if ( err )
		throw std::runtime_error( "Problem creating thread" );
	#endif
}

void Thread::kill( int signal )
{
	#ifndef WIN32 // UNIX
	int err = pthread_kill( *threadID_, signal );
	if ( err )
		throw std::runtime_error( "Problem killing/signaling thread" );
	#endif
}

void Thread::join( )
{
	#ifndef WIN32 //UNIX
	int err = pthread_join( *threadID_, NULL );
	if( err )
		 std::runtime_error( "Problem Joining Thread" );
	#endif
}
