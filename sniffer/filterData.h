
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
