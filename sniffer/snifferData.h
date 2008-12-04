
#ifndef SNIFFERDATA_H
#define SNIFFERDATA_H

#include <pthread.h>
#include <fstream>
#include <string>
#include "baseData.h"

class SnifferData : public BaseData
{
	public:
		SnifferData( Mutex &coutMutex, Mutex &logMutex,
				std::ofstream *log );
		void setDevice( std::string device );
		std::string getDevice( );
	private:
		std::string device_;
};

#endif 
