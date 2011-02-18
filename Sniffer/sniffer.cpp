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

std::ofstream sniffer::log_stream(logFile.c_str(), std::ios::out|std::ios::app);
const std::string sniffer::logFile = "./sniffer.log";

/**
	Constructor to initialize member data and base class data
*/
sniffer::sniffer():snifferData( coutMutex, logMutex, &log_stream ), sniffing_(false)
{
	filterData = new FilterData ( coutMutex, logMutex, &log_stream );
	setStartRoutine(run_sniffer);
}

/**
    Pop single packet from doubly-ended-queue containing sniffed packets
*/
Packet sniffer::popPacket()
{
	return filterData->popPacket( );
}

/**
    Start the sniffer to allow packet sniffing 
*/
void sniffer::start()
{
	MutexLocker lock( sniffingMutex_ );
  sniffing_=true;
	lock.unlock();
	Thread::start(this);
}

/**
    set pcap file as logical input device for sniffing packets
*/
void sniffer::setInputPcapFile(std::string pcapFile)
{
	inDev_.setDevice( pcapFile, 0);
}

/**
	Return input device name used for packet sniffing
*/
std::string sniffer::getInputDevice( )
{
	return inDev_.getDevice();
}

/**
	set pcap file as an output for sniffed packets
*/
void sniffer::setOutPcapFile(std::string pcapFile)
{
	outDev_.setDevice( pcapFile, 0);
}

/**
	return name of output device used for dumping sniffed packets
*/
std::string sniffer::getOutputDevice( )
{
	return outDev_.getDevice();
}

/**
	Set filter expression for sniffing packets
*/
void sniffer::setFilter(std::string filter)
{
	filter_ = filter;
}

/**
	Log intermediate messages in a thread-safe manner 
*/
void sniffer::log( std::string message )
{
	logMutex.lock();
	log_stream << message << std::endl;
	logMutex.unlock();
}

/**
	Set input device which should be used for sniffing packets
*/
void sniffer::setInputDevice( std::string device )
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
	sniffer *tempSniffer = (sniffer*) data;
	tempSniffer->packetSniffer();
}

/**
  *	Function to start actual packet sniffing once the sniffer has been started using 'start' method. 
  * It takes care of both physical and logical device as input nad writes into doubly-ended-queue or another pcap file as specified by the user
  */
void* sniffer::packetSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t* args = (uint8_t*)filterData;

	snifferData.log( "SnifferOffline Started!" ); 
	snifferData.log( "Opening File: " + inDev_.getDevice() );

	// 65535 from pcap man page...
	pcap_t* pcap_ptr;
	//if(inPcapFile_.size())
	if(!inDev_.isDevice())
		pcap_ptr = pcap_open_offline( (inDev_.getDevice()).c_str(), errbuf );
	else
	{
		if( inDev_.getDevice() == "any" )
			pcap_ptr = pcap_open_live( "any", 65535, 1, -1, errbuf );
		else
			pcap_ptr = pcap_open_live( (inDev_.getDevice()).c_str(), 500, 1, 40, errbuf );
	}

	if ( pcap_ptr == NULL )
	{
		snifferData.log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
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

	if ((outDev_.getDevice()).size() != 0)
	{
		pcap_dumper_t *dumpfile; 
		struct pcap_pkthdr *header;
		const u_char *pkt_data;
		dumpfile= pcap_dump_open(pcap_ptr, (outDev_.getDevice()).c_str());

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

		filterData->setPcapPointer( pcap_ptr );

		while( err == -2 )
		{
			snifferData.log( "Sniffer processing packets" );
			err = pcap_loop( pcap_ptr, -1, my_callback, args );
			snifferData.log( "Sniffer had to stop processing packets" );
			usleep(1);
		}
	}

	MutexLocker lock( sniffingMutex_ );
	sniffing_ = false;
	filterData->pushPacket( Packet() );
	

	snifferData.log( "SnifferOffline Stopping!" );
}

bool sniffer::sniffing() 
{
	MutexLocker lock( sniffingMutex_ );
	return sniffing_;
}

/**
	Method to print all the devices in the system 
*/
void sniffer::printDevices()
{
	
	pcap_if_t *alldevs;
	char errbuf[PCAP_ERRBUF_SIZE+1];
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
		std::exit(1);
	}
	/* Scan the list printing every entry */
	for(pcap_if_t* dev=alldevs;dev != NULL;dev=dev->next)
	{
		/* Name */
		std::cout << dev->name << std::endl;
		/* Description */
		if (dev->description)
		{
			std::cout << "\tDescription: " << dev->description << std::endl;
		}
		/* Loopback Address*/
		std::cout << "\tLoopback: " << ((dev->flags & PCAP_IF_LOOPBACK)?"yes":"no") << std::endl;
		/* IP addresses */
		for(pcap_addr_t *addrEl=dev->addresses;addrEl != NULL;addrEl=addrEl->next)
		{
			if( addrEl->addr )//Needed incase of a tun interface
			{
				std::cout << "\tAddress Family: " << addrEl->addr->sa_family << std::endl;
				switch(addrEl->addr->sa_family)
				{
					case AF_INET:
						std::cout << "\tAddress Family Name: AF_INET" << std::endl;
						if (addrEl->addr)
							std::cout << "\tAddress: " << 
								iptos(((struct sockaddr_in *)addrEl->addr)->sin_addr.s_addr) << std::endl;
						if (addrEl->netmask)
							std::cout << "\tNetmask: " << 
								iptos(((struct sockaddr_in *)addrEl->netmask)->sin_addr.s_addr) << std::endl;
						if (addrEl->broadaddr)
							std::cout << "\tBroadcast Address: " << 
								iptos(((struct sockaddr_in *)addrEl->broadaddr)->sin_addr.s_addr) << std::endl;
						if (addrEl->dstaddr)
							std::cout << "\tDestination Address: " << 
								iptos(((struct sockaddr_in *)addrEl->dstaddr)->sin_addr.s_addr) << std::endl;
						break;
					case AF_INET6:
						std::cout << "\tAddress Family Name: AF_INET6" << std::endl;
						break;
					default:
						std::cout << "\tAddress Family Name: Unknown" << std::endl;
						break;
				}
			}
			std::cout << std::endl;
		} 
	}

	/* Free the device list */

	pcap_freealldevs(alldevs);
} 

/**
	Converts an input ip in decimal format into human-readable string format
*/
std::string sniffer::iptos(u_long in)
{
	std::stringstream output;
	u_char *pByte;
	pByte = (u_char *)&in;
	output << (unsigned int) pByte[0]
		<< "." << (unsigned int) pByte[1]
		<< "." << (unsigned int) pByte[2]
		<< "." << (unsigned int) pByte[3] << std::flush;
	return output.str();
} 

