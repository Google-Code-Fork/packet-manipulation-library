/**
 * * INAV - Interactive Network Active-traffic Visualization
 * * Copyright � 2007  Nathan Robinson, Jeff Scaparra
 * *
 * * This file is a part of INAV.
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
#include <errno.h>
Mutex::Mutex( MutexType type )
{
#ifndef WIN32 // UNIX

	mutexAttr_ = new pthread_mutexattr_t;
	//Create a default mutex attribute
	pthread_mutexattr_init(mutexAttr_);

	if( type == Normal )
		pthread_mutexattr_settype(mutexAttr_, PTHREAD_MUTEX_NORMAL);

	mutex_ = new pthread_mutex_t;
	int err = pthread_mutex_init( mutex_, mutexAttr_ );
	//int err = pthread_mutex_init( mutex_, NULL );
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

	pthread_mutexattr_destroy( mutexAttr_ );
#endif
}

Mutex::Mutex( const Mutex& mutex )
{
  throw std::runtime_error( "Mutex copy constructor: I this this will cause a double free");
#ifndef WIN32 //UNIX
	mutex_ = mutex.mutex_;
#endif
}

Mutex& Mutex::operator=(const Mutex& mutex )
{
  throw std::runtime_error( "Mutex copy constructor: I this this will cause a double free");
#ifndef WIN32 //UNIX
	mutex_ = mutex.mutex_;
#endif
	return *this;
}

void Mutex::lock()
{
#ifndef WIN32 // UNIX
	if( pthread_mutex_lock( mutex_ ) != 0 )
		throw std::runtime_error( "Can't lock Mutex" );
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
