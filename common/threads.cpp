/**
 * * PacMan - Packet Manipulation Library
 * * Copyright (C) 2011  Jeff Scaparra
 * *
 * * This file is a part of PacMan.
 * *
 * * This program is free software: you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation, either version 3 of the License, or
 * * (at your option) any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

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

void Thread::setStartRoutine( StartRoutine routine)
{
	startRoutine_ = routine;
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

void Thread::stop()
{
	#ifndef WIN32 //UNIX
	int err = pthread_cancel( *threadID_ );
	if( err )
		std::runtime_error( "Problem stopping thread !!" );
	#endif
	join();
}

