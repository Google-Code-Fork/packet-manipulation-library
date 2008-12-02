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


#include "filterData.h"
#include <iostream>

FilterData::FilterData( Mutex &coutMutex, Mutex &logMutex, std::ofstream *log ): BaseData( coutMutex, logMutex, log)
{
	Semaphore semaphore_;
}

void FilterData::pushPacket( Packet packet )
{
	if( filter( packet ) )
	{
		incommingPacketsMutex_.lock( );
		incommingPackets_.push_back( packet );
		semaphore_.post();
		incommingPacketsMutex_.unlock( );
	}

}

Packet FilterData::popPacket( )
{
	semaphore_.wait();
	incommingPacketsMutex_.lock( );
	Packet packet = incommingPackets_.at( 0 );
	incommingPackets_.pop_front();
	incommingPacketsMutex_.unlock( );
	return packet;
}

int FilterData::size()
{
	incommingPacketsMutex_.lock( );
	int size = incommingPackets_.size();
	incommingPacketsMutex_.unlock( );
	return size;
}

bool FilterData::filter( Packet packet )
{
	//only allow ip packets through
	//if( packet.inetIs<IPv4>() )
//		return true; 
	return false;
}

void FilterData::setPcapPointer( pcap_t* pointer )
{
	pcapPointer_ = pointer;
}

pcap_t* FilterData::getPcapPointer( )
{
	return pcapPointer_;
}
