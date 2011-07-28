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


#include "filterData.h"
#include <iostream>

/**
	Constructor to initialize member data and base class data
*/
FilterData::FilterData( Mutex &coutMutex, Mutex &logMutex, std::ofstream *log ): BaseData( coutMutex, logMutex, log)
{
	Semaphore semaphore_;
}

/**
	Push packets into a doubly-ended-queue in a thread-safe manner
*/
void FilterData::pushPacket( Packet packet )
{
		incommingPacketsMutex_.lock( );
		incommingPackets_.push_back( packet );
		semaphore_.post();
		incommingPacketsMutex_.unlock( );
}

/**
	Pop packets from a doubly-ended-queue in a thread-safe manner
*/
Packet FilterData::popPacket( )
{
	semaphore_.wait();
	incommingPacketsMutex_.lock( );
	Packet packet = incommingPackets_.at( 0 );
	incommingPackets_.pop_front();
	incommingPacketsMutex_.unlock( );
	return packet;
}

void FilterData::clearPackets()
{
  MutexLocker lock( incommingPacketsMutex_ );
  semaphore_.setNum( 0 );
  incommingPackets_.clear();
}

/**
	Return number of packets currently in the queue 
*/
int FilterData::size()
{
	incommingPacketsMutex_.lock( );
	int size = incommingPackets_.size();
	incommingPacketsMutex_.unlock( );
	return size;
}

/**
	Set current pcap pointer 
*/
//void FilterData::setPcapPointer( pcap_t* pointer )
//{
//	pcapPointer_ = pointer;
//}

/**
	Return current pcap pointer
*/
//pcap_t* FilterData::getPcapPointer( )
//{
//	return pcapPointer_;
//}
