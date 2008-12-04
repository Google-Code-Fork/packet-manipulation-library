
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
	return true;
}

void FilterData::setPcapPointer( pcap_t* pointer )
{
	pcapPointer_ = pointer;
}

pcap_t* FilterData::getPcapPointer( )
{
	return pcapPointer_;
}
