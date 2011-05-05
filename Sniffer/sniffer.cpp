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


#include<iostream>
#include<string>
#include<sstream>
#include<pthread.h>
#include<pcap.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/ip.h>
#include<algorithm>
#include<stdexcept>
#include"sniffer.h"
#include"snifferData.h"
#include"filterData.h"
#include"constants.h"

const std::string Sniffer::logFile_ = "./sniffer.log";
std::ofstream Sniffer::log_stream_(logFile_.c_str(), std::ios::out|std::ios::app);

const uint32_t Sniffer::DEFAULT_SNAP_LENGTH = 65535;
/**
	Constructor to initialize member data and base class data
*/
Sniffer::Sniffer():snifferData_( SnifferData( coutMutex_, logMutex_, &log_stream_ ) ), sniffing_(false), snapLength_(
		DEFAULT_SNAP_LENGTH)
{
	filterData_ = new FilterData ( coutMutex_, logMutex_, &log_stream_ );
	setStartRoutine(run_sniffer);
}

/**
    Pop single packet from doubly-ended-queue containing sniffed packets
*/
Packet Sniffer::popPacket()
{
	return filterData_->popPacket( );
}

/**
    Start the sniffer to allow packet sniffing 
*/
void Sniffer::start()
{
	MutexLocker lock( sniffingMutex_ );
  sniffing_=true;
	lock.unlock();
	Thread::start(this);
}

/**
    set pcap file as logical input device for sniffing packets
*/
void Sniffer::setInputPcapFile( const std::string &pcapFile)
{
	inDev_.setDevice( pcapFile, 0);
}

/**
	Return input device name used for packet sniffing
*/
std::string Sniffer::inputDevice( ) const
{
	return inDev_.device();
}

/**
	set pcap file as an output for sniffed packets
*/
void Sniffer::setOutPcapFile( const std::string &pcapFile )
{
	outDev_.setDevice( pcapFile, 0);
}

/**
	return name of output device used for dumping sniffed packets
*/
std::string Sniffer::outputDevice( ) const
{
	return outDev_.device();
}

/**
	Set filter expression for sniffing packets
*/
void Sniffer::setFilter(const std::string &filter)
{
	filter_ = filter;
}

/**
	Log intermediate messages in a thread-safe manner 
*/
void Sniffer::log( const std::string &message )
{
	MutexLocker lock( logMutex_ );
	log_stream_ << message << std::endl;
}

/**
	Set input device which should be used for sniffing packets
*/
void Sniffer::setInputDevice( const std::string &device )
{
	inDev_.setDevice( device , 1);
}

/**
	Callback function used for capturing sniffed packets
*/
void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture )
{
	FilterData* filterData = (FilterData*)args;
	if( filterData->size() >= sniff::MAX_PACKETS_QUEUED )
	{
		pcap_breakloop( filterData->getPcapPointer() );
	}
	try
	{
		PacketBuilder pb;
		Packet packet = pb.buildPacket<Ethernet>(PacketBuffer(packetCapture, pkthdr->caplen));
		packet.setTimestamp( pkthdr->ts );
		filterData->pushPacket( packet );
	}
	catch( std::runtime_error e )
	{
		if( (std::string)e.what() == "Malformed Packet" )
			return;
		else
			throw e;
	}
}

/**
	Starting method used by sniffer to start packet sniffing
*/
void* run_sniffer(void* data)
{
	Sniffer *tempSniffer = (Sniffer*) data;
	tempSniffer->packetSniffer();
}

/**
  *	Function to start actual packet sniffing once the sniffer has been started using 'start' method. 
  * It takes care of both physical and logical device as input nad writes into doubly-ended-queue or another pcap file as specified by the user
  */
void* Sniffer::packetSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t* args = (uint8_t*)filterData_;

	snifferData_.log( "SnifferOffline Started!" ); 
	snifferData_.log( "Opening File: " + inDev_.device() );

	// 65535 from pcap man page...
	pcap_t* pcap_ptr;
	//if(inPcapFile_.size())
	if(!inDev_.isDevice())
		pcap_ptr = pcap_open_offline( (inDev_.device()).c_str(), errbuf );
	else
	{
		if( inDev_.device() == "any" )
			pcap_ptr = pcap_open_live( "any", snapLength_, 1, 500, errbuf );
		else
			pcap_ptr = pcap_open_live( (inDev_.device()).c_str(), snapLength_, 1, 500, errbuf );
	}

	if ( pcap_ptr == NULL )
	{
		snifferData_.log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
		std::cerr << "Sniffer ERROR: " << errbuf << std::endl;
		std::exit(-1);
	}


	if (filter_.size())
	{
		struct bpf_program fcode;
		bpf_u_int32 NetMask;
		NetMask=0xffffff;

		//compile the filter
		if(pcap_compile(pcap_ptr, &fcode, filter_.c_str(), 1, NetMask) < 0)
		{
			fprintf(stderr,"\nError compiling filter: wrong syntax.\n");
			std::exit(1);
		}

		//set the filter
		if(pcap_setfilter(pcap_ptr, &fcode)<0)
		{
			fprintf(stderr,"\nError setting the filter\n");
			std::exit(1);
		}
	}

	if ((outDev_.device()).size() != 0)
	{
		pcap_dumper_t *dumpfile; 
		struct pcap_pkthdr *header;
		const u_char *pkt_data;
		dumpfile= pcap_dump_open(pcap_ptr, (outDev_.device()).c_str());

		if (dumpfile == NULL)
		{
			fprintf(stderr,"\nError opening output file\n");
			return NULL;
		}

		int res;
		while((res = pcap_next_ex( pcap_ptr, &header, &pkt_data)) >= 0)
		{

			if(res == 0)
				continue;  	/* Timeout elapsed */

			//save the packet on the dump file
			pcap_dump((unsigned char *) dumpfile, header, pkt_data);

		}
	}
	else
	{
		int err = -2;//this is the return value of pcap_loop if stoped with pcap_breakloop()

		filterData_->setPcapPointer( pcap_ptr );

		while( err == -2 )
		{
			snifferData_.log( "Sniffer processing packets" );
			err = pcap_loop( pcap_ptr, -1, my_callback, args );
			snifferData_.log( "Sniffer had to stop processing packets" );
			usleep(1);
		}
	}

	MutexLocker lock( sniffingMutex_ );
	sniffing_ = false;
	filterData_->pushPacket( Packet() );
	

	snifferData_.log( "SnifferOffline Stopping!" );
}

bool Sniffer::sniffing() const 
{
	MutexLocker lock( sniffingMutex_ );
	return sniffing_;
}

/**
	Method to print all the devices in the system 
*/
void Sniffer::printDevices() const
{
	DevicesLookup lookup;
	lookup.printAllDevices();
} 

void Sniffer::setSnapLength( const uint32_t &snaplen )
{
	snapLength_ = snaplen;
}

uint32_t Sniffer::snapLength( ) const
{
	return snapLength_;
}
