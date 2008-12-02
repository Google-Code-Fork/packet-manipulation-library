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


#ifndef FILTERDATA_H
#define FILTERDATA_H

#include <fstream>
#include <deque>
#include <string>
#include <pcap.h>
#include "../common/threads.h"
#include "baseData.h"
#include "../Packet/packetBuilder.h"

class FilterData : public BaseData
{
	public:
		FilterData( Mutex &coutMutex, Mutex &logMutex,
				std::ofstream *log );
		void pushPacket( Packet packet );
		Packet popPacket( );
		int size();
		void setPcapPointer( pcap_t* pointer );
		pcap_t* getPcapPointer();

	private:
		pcap_t* pcapPointer_;
		bool filter( Packet packet );
		std::deque< Packet > incommingPackets_;
		Mutex incommingPacketsMutex_;
		Semaphore semaphore_;
};





#endif 
