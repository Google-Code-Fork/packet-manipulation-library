/**
 * * PacMan - Packet Manipulation Library
 * * Copyright (C) 2011 Jeff Scaparra 
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

#ifndef THREADS_H
#define THREADS_H

#ifdef WIN32
// Windows specific headers

#endif
#ifndef WIN32
// Unix headers
#include <pthread.h>
#include <errno.h>
#include <stdexcept>
#include "pthreaderrors.h"
#include "uncopyable.h"
#include <time.h>
#include "deprecated.h"

typedef void*(*StartRoutine)(void*);
#endif

class Thread : private Uncopyable
{
	public: 
		Thread();
		Thread(StartRoutine);
		~Thread();
		void setStartRoutine( StartRoutine ); 
		void start( void * dataForThread );
		void kill( int signal );
		void stop();
		void join();

	private:
    //Not Copyable

    StartRoutine startRoutine_;
		#ifndef WIN32 // UNIX
		pthread_t * threadID_;
		#endif
};

enum MutexType{ Normal };

class Mutex : private Uncopyable
{
	public:
		Mutex( MutexType = Normal );
		~Mutex();
		void lock();
		int trylock(); //return 0 on success
		void unlock();

  private:
#ifndef WIN32 //UNIX
		pthread_mutex_t* mutex_;
		pthread_mutexattr_t* mutexAttr_;
#endif
    friend class Condition;
};

class Condition : private Uncopyable
{
  public:
    Condition( );
    virtual ~Condition();
    void signal( );
    void broadcast( );
    void wait( Mutex &mutex );
    //!Returns true if signaled, false if timed out
    bool timeWait( Mutex &mutex, const timespec &waitTime );

  private:
    pthread_cond_t* cond_;
    pthread_condattr_t *cond_attr_;
};

class MutexLocker : private Uncopyable
{
  public:
    MutexLocker( Mutex & m ):m_(m), locked_(true)
    {
      m_.lock();
    }

    ~MutexLocker()
    {
      if(locked_)
	m_.unlock();
    }

    void unlock()
    {
      m_.unlock();
      locked_=false;
    }

    void lock()
    {
      m_.lock();
      locked_=true;
    }

  private:
    Mutex &m_;
    bool locked_;
};


class Semaphore : private Uncopyable
{
	public:
		Semaphore( int num = 0 );
		virtual ~Semaphore();
		void post();
		void wait();
    DEPRECATED(int getNum() const);
    int count() const;
    void setNum( int num );

	private: 
#ifndef WIN32 //UNIX
		int num_;
    mutable pthread_mutex_t count_mutex;
    mutable pthread_cond_t count_condition;
#endif
};

class ReaderWriterLock : private Uncopyable
{
  public:
    ReaderWriterLock();
    virtual ~ReaderWriterLock();
    void readLock();
    void readUnlock();
    void writeLock();
    void writeUnlock();

  private:
    int num_;
    pthread_mutex_t countMutex_;
    pthread_cond_t countCondition_;
    pthread_mutex_t writerMutex_;
    pthread_cond_t noMoreReaders_;
    pthread_mutex_t writerWaiting_;

    inline int getNum();
    inline void readerPost();
    inline void readerWait();
};

class ReadLocker : private Uncopyable
{
  public:
    ReadLocker( ReaderWriterLock & m ):m_(m), locked_(true)
    {
      m_.readLock();
    }

    ~ReadLocker()
    {
      if(locked_)
	m_.readUnlock();
    }

    void unlock()
    {
      m_.readUnlock();
      locked_=false;
    }

    void lock()
    {
      m_.readLock();
      locked_=true;
    }

  private:
    ReaderWriterLock &m_;
    bool locked_;
};

class WriteLocker : private Uncopyable
{
  public:
    WriteLocker( ReaderWriterLock & m ):m_(m), locked_(true)
    {
      m_.writeLock();
    }

    ~WriteLocker()
    {
      if(locked_)
	m_.writeUnlock();
    }

    void unlock()
    {
      m_.writeUnlock();
      locked_=false;
    }

    void lock()
    {
      m_.writeLock();
      locked_=true;
    }

  private:
    ReaderWriterLock &m_;
    bool locked_;
};

#endif 
