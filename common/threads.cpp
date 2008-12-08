/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2008  Jeff Scaparra, Gaurav Yadav, Andrie Tanusetiawan
 *
 * This file is a part of PacMan.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "threads.h"
#include <stdexcept>
#ifndef WIN32 // UNIX
#include <signal.h>
#endif

/**
	Constructor to initialize member data
*/
Thread::Thread( )
{
	#ifndef WIN32 //UNIX
	threadID_ = new pthread_t;
	#endif
}

/**
	Stop currently running thread
*/
void Thread::stop()
{
	#ifndef WIN32 //UNIX
	int err = pthread_cancel( *threadID_ );
	if( err )
		 std::runtime_error( "Problem stopping thread !!" );
	#endif
	join();
}

/**
	Contructor to initialize member data as well as set thread 'start' routine
*/
Thread::Thread( StartRoutine routine ):startRoutine_(routine)
{
	#ifndef WIN32 //UNIX
	threadID_ = new pthread_t;
	#endif
}

/**
	Set thread 'start' routine
*/
void Thread::setStartRoutine( StartRoutine routine)
{
	startRoutine_ = routine;
}

/**
	Contructor to initialize member data 
*/
Thread::~Thread( )
{
	delete threadID_;
}

/**
	Copy Contructor 
*/
Thread::Thread( const Thread & thread )
{
	#ifndef WIN32 //UNIX
	if( threadID_ == NULL )
		threadID_ = new pthread_t;
	startRoutine_ = thread.startRoutine_;
	threadID_ = thread.threadID_;
	#endif
}

/**
	Start this thread to make it run using using 'startRoutine_,' as the starting soutine and 'dataForThread' a its argument
*/
void Thread::start( void * dataForThread )
{
	#ifndef WIN32 // UNIX
	int err = pthread_create( threadID_, NULL, startRoutine_, dataForThread );
	if ( err )
		throw std::runtime_error( "Problem creating thread" );
	#endif
}

/**
	Kill 'this' running thread
*/
void Thread::kill( int signal )
{
	#ifndef WIN32 // UNIX
	int err = pthread_kill( *threadID_, signal );
	if ( err )
		throw std::runtime_error( "Problem killing/signaling thread" );
	#endif
}

/**
	Wait for 'this' thread to join with parent process
*/
void Thread::join( )
{
	#ifndef WIN32 //UNIX
	int err = pthread_join( *threadID_, NULL );
	if( err )
		 std::runtime_error( "Problem Joining Thread" );
	#endif
}
