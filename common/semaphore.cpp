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

/**
	Constructor to initialize member data
*/
Semaphore::Semaphore( int num ):num_(num)
{
	pthread_mutex_init( &count_mutex, NULL );
	pthread_cond_init( &count_condition, NULL );
	if( num_ > 0 )
	{
		pthread_cond_signal(&count_condition);
	}
}

/**
	Obtain a Lock, increment data, post the signal and release the lock 
*/
void Semaphore::post()
{
	pthread_mutex_lock( &count_mutex );
	++num_;
	pthread_cond_signal( &count_condition );
	pthread_mutex_unlock( &count_mutex );
}

/**
	Wait untill someone signals 'post' i.e. makes member data non-zero
*/
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

/**
	Return current data member value
*/
int Semaphore::getNum()
{
	pthread_mutex_lock( &count_mutex );
	int tmp = num_;
	pthread_mutex_unlock( &count_mutex );
	return tmp;
}
