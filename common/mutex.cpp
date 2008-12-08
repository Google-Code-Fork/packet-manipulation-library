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
