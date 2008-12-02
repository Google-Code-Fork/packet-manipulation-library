/**
 * * INAV - Interactive Network Active-traffic Visualization
 * * Copyright © 2007  Nathan Robinson, Jeff Scaparra
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

#ifndef THREADS_H
#define THREADS_H

#ifdef WIN32
// Windows specific headers

#endif
#ifndef WIN32
// Unix headers
#include <pthread.h>
typedef void*(*StartRoutine)(void*);
#endif

class Thread
{
	public: 
		Thread(StartRoutine);
		~Thread();
		Thread(const Thread& thread );
		void start( void * dataForThread );
		void kill( int signal );
		void join();

	private:
		StartRoutine startRoutine_;
		#ifndef WIN32 // UNIX
		pthread_t * threadID_;
		#endif
};

class Mutex
{
	public:
		Mutex();
		~Mutex();
		Mutex( const Mutex& mutex );
		void lock();
		int trylock(); //return 0 on success
		void unlock();

	private:
#ifndef WIN32 //UNIX
		pthread_mutex_t* mutex_;
#endif
};

class Semaphore
{
	public:
		Semaphore( int num = 0 );
		void post();
		void wait();
		int getNum();

	private: 
#ifndef WIN32 //UNIX
		int num_;
		pthread_mutex_t count_mutex;
		pthread_cond_t count_condition;
#endif
};


#endif 
