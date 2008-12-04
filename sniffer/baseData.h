
#ifndef BASEDATA_H
#define BASEDATA_H

#include <fstream>
#include <string>
#include "../common/threads.h"

class BaseData
{
	public:
		BaseData( Mutex& coutMutex, Mutex& logMutex,
				std::ofstream *log );
		Mutex& getCoutMutex();
		void setCoutMutex( Mutex& coutMutex );
		void setLogMutex( Mutex& logMutex );
		Mutex& getLogMutex ();
		void print( std::string message );
		void log( std::string message );

//	private:
	protected:
		Mutex& coutMutex_;
		Mutex& logMutex_;
		std::ofstream *log_;

};





#endif 
