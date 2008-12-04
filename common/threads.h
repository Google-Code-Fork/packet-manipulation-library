
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
		Thread();
		Thread(StartRoutine);
		~Thread();
		Thread(const Thread& thread );
		void setStartRoutine( StartRoutine );
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
