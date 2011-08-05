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
#include"../common/helper.h"

const std::string Sniffer::logFile_ = "./sniffer.log";
std::ofstream Sniffer::log_stream_(logFile_.c_str(), std::ios::out|std::ios::app);

const uint32_t Sniffer::DEFAULT_SNAP_LENGTH = 65535;
/**
	Constructor to initialize member data and base class data
*/
Sniffer::Sniffer():snifferData_( SnifferData( coutMutex_, logMutex_, &log_stream_ ) ), sniffing_(false), snapLength_(
		DEFAULT_SNAP_LENGTH), numberOfRunningThreads_(0)
{
	filterData_ = new FilterData ( coutMutex_, logMutex_, &log_stream_ );
}

Sniffer::~Sniffer()
{
  MutexLocker lock( sniffingMutex_ );
  if( sniffing_ ) //This is the keep the mutexes in filterData to be locked by other threads
  {
    lock.unlock();
    stop();
  }
  delete filterData_;
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
	if( sniffing_ ) //Don't start more threads if already sniffing
		return;
  sniffing_=true;
  filterData_->clearPackets();
  lock.unlock();
  for( uint32_t i = 0; i < snifferDevices_.size(); ++ i )
	{
    SmartPtr< Thread > thread = new Thread;
    thread->setStartRoutine( run_sniffer );
    thread->start( this );
		threads_.push_back( thread );
		log( "Started sniffer " );
	}
}

/**
    set pcap file as logical input device for sniffing packets
*/
void Sniffer::setInputPcapFile( const std::string &pcapFile)
{
	Device device;
	device.setDevice( pcapFile, 0);
	snifferDevices_.push_back( device );
}

void Sniffer::setInputPcapFiles( const std::vector< std::string > &pcaps )
{
  for( uint32_t i = 0; i < pcaps.size(); ++i )
	{
		Device device;
		device.setDevice( pcaps[i], 0 );
		snifferDevices_.push_back( device );
	}
}

/**
	Return input device name used for packet sniffing
*/
std::vector< std::string > Sniffer::inputDevices( ) const
{
	std::vector< std::string > devices;
  for( uint32_t i = 0; i < snifferDevices_.size(); ++i )
	{
		devices.push_back( snifferDevices_[i].device() );
	}
	return devices;
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
  //filters not working on lion... :(
#ifndef __APPLE__
	filter_ = filter;
#endif
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
	snifferDevices_.clear();
	addInputDevice( device );
}

/**
 * Adds Device to list of input devices
 */
void Sniffer::addInputDevice( const std::string &deviceName )
{
	Device device;
	device.setDevice( deviceName , 1);
	snifferDevices_.push_back( device );
}

/**
	Callback function used for capturing sniffed packets
*/
void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture )
{
	ThreadData* threadData = (ThreadData*)args;
	FilterData* filterData = threadData->filterData;
  if( filterData->size() >= sniff::MAX_PACKETS_QUEUED )
	{
		pcap_breakloop( threadData->pcapPointer );
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

  return NULL;
}

/**
  *	Function to start actual packet sniffing once the sniffer has been started using 'start' method. 
  * It takes care of both physical and logical device as input nad writes into doubly-ended-queue or another pcap file as specified by the user
  */
void* Sniffer::packetSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	ThreadData threadData;
	uint8_t* args = (uint8_t*)&threadData;

	MutexLocker lock( threadNumMutex_ );
	Device inDev = snifferDevices_[ numberOfRunningThreads_++ ];
  lock.unlock();
	
	snifferData_.log( "SnifferOffline Started!" ); 
	snifferData_.log( "Opening File: " + inDev.device() );

	pcap_t* pcap_ptr;

	if(!inDev.isDevice())
		pcap_ptr = pcap_open_offline( (inDev.device()).c_str(), errbuf );
	else
	{
		if( inDev.device() == "any" )
			pcap_ptr = pcap_open_live( "any", snapLength_, 1, 500, errbuf );
		else
			pcap_ptr = pcap_open_live( (inDev.device()).c_str(), snapLength_, 1, 500, errbuf );
	}

	if ( pcap_ptr == NULL )
	{
		snifferData_.log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
		std::cerr << "Sniffer ERROR: " << errbuf << std::endl;
		std::exit(-1);
	}

  pcap_ptrs_.push_back( pcap_ptr );


	if (filter_.size())
	{
		struct bpf_program fcode;
		bpf_u_int32 NetMask;
    NetMask=0xffffff;
    //PCAP_NETMASK_UNKNOWN not declared on mac
    //NetMask=PCAP_NETMASK_UNKNOWN;

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

		threadData.filterData = filterData_;
		threadData.pcapPointer = pcap_ptr;

    struct timespec sleeptime;
    sleeptime.tv_sec = 0;
    sleeptime.tv_nsec = 10;
		while( err == -2 )
    {
			snifferData_.log( "Sniffer processing packets" );
			err = pcap_loop( pcap_ptr, -1, my_callback, args );
      snifferData_.log( "Sniffer had to stop processing packets" );
      if( err == -2 )
        nanosleep( &sleeptime, NULL );
      if( err > 0 )
        snifferData_.log( "Sniffer processed " + ss_itoa< int >( err ) );
		}
	}

	MutexLocker lock2( sniffingMutex_ );
  sniffing_ = false;
  //flush out anything waiting on a packet with empty packets
  for( int i = 0; i < 100; ++ i )
    filterData_->pushPacket( Packet() );

  numberOfRunningThreads_ --;
  snifferData_.log( "Sniffer Stopping!" );
  return NULL;
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

void Sniffer::stop() 
{
	MutexLocker lockThreads( threadNumMutex_ );
	MutexLocker lockSniffer( sniffingMutex_ );
  for( uint i = 0; i < pcap_ptrs_.size(); ++i )
  {
    pcap_breakloop( pcap_ptrs_[i] );
  }
  if( sniffing_ )
  {
    numberOfRunningThreads_ = 0;
    sniffing_ = false;
    for( uint32_t i = 0; i < threads_.size(); ++i )
    {
      threads_[i]->stop();
    }
    //flush out anything waiting on a packet with empty packets
    for( uint i = 0; i < 100; ++i )
      filterData_->pushPacket( Packet() );
  }
}

void Sniffer::restart()
{
	stop();
	start();
}
