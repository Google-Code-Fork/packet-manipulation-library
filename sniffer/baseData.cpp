
#include "baseData.h"
#include <iostream>

BaseData::BaseData( Mutex & coutMutex,
Mutex & logMutex,
std::ofstream *log ):coutMutex_(coutMutex),
logMutex_(logMutex),
log_(log)
{
}

Mutex & BaseData::getCoutMutex ()
{
	return coutMutex_;
}

void BaseData::setCoutMutex ( Mutex & coutMutex )
{
	coutMutex_ = coutMutex;
}

void BaseData::setLogMutex ( Mutex & logMutex )
{
	logMutex_ = logMutex;
}

Mutex & BaseData::getLogMutex ()
{
	return logMutex_;
}

void BaseData::print ( std::string message )
{
	coutMutex_.lock();
	std::cout << message << std::endl;
	coutMutex_.unlock();
}

void BaseData::log ( std::string message )
{
	logMutex_.lock();
	*log_ << message << std::endl;
	logMutex_.unlock();
}
