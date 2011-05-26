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
