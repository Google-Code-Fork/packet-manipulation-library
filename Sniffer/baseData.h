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
