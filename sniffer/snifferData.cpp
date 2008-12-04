
#include "snifferData.h"
#include <iostream>

SnifferData::SnifferData( Mutex &coutMutex, Mutex &logMutex, std::ofstream *log ): BaseData( coutMutex, logMutex, log)
{
	device_="all";
}

void SnifferData::setDevice( std::string device )
{
	device_ = device;
}

std::string SnifferData::getDevice()
{
	return device_;
}

