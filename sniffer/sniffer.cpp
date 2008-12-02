/**
#include "clientCommData.h"
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


#include<iostream>
#include<string>
#include<sstream>
#include<pthread.h>
#include<pcap.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
//#include<netinet/if_ether.h>
//#include<net/ethernet.h>
//#include<netinet/ether.h>
#include<unistd.h>
#include<netinet/ip.h>
#include<algorithm>
#include<stdexcept>
#include"sniffer.h"
#include"snifferData.h"
#include"filterData.h"
#include"constants.h"
#include"../common/parseCommas.h"

std::ofstream sniffer::log_stream(logFile.c_str(), std::ios::out|std::ios::app);
const std::string sniffer::logFile = "./inavd.log";

Packet sniffer::popPacket()
{
	return filterData->popPacket();
}

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture )
{
	std::cout<<"\n callback called";
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
/*	if(filterData->size())
	{
		Packet packet = filterData->popPacket();
		time_t mytime = time(0);
		std::cout<<"\n"<<asctime(localtime(&mytime));
		if(packet.isIP())
		{
			std::cout<<"IP ==> ";
			std::cout<<packet.getSourceMAC()<<" / ";
			std::cout<<packet.getDestinationMAC()<<" / ";
			std::cout<<packet.getType()<<" / ";
			std::cout<<packet.getIPVersion()<<" / ";
			std::cout<<packet.getProtocol()<<" / ";
		}
		if(packet.isTCP())
		{
			std::cout<<"\nTCP ==> ";
			std::cout<<packet.getTCPSourcePort()<<" / ";
			std::cout<<packet.getTCPDestinationPort()<<" / ";
			std::cout<<packet.getType()<<" / ";
			std::cout<<packet.getIPVersion()<<" / ";
			std::cout<<packet.getIPIdentification()<<" / ";
			std::cout<<packet.getProtocol()<<" / ";
			std::cout<<(sniffer::iptos(packet.getSourceAddress())).c_str()<<" / ";
			std::cout<<(sniffer::iptos(packet.getDestinationAddress())).c_str()<<" / ";
		}
	}*/
}


void* run_devSniffer(void* data)
{
	sniffer *tempSniffer = (sniffer*) data;
	tempSniffer->devSniffer();
}

void* run_offlineSniffer(void* data)
{
	sniffer *tempSniffer = (sniffer*) data;
	tempSniffer->offlineSniffer();
}

void sniffer::setDebug(bool value)
{
	DEBUG = value;
}

void sniffer::log( std::string message )
{
	logMutex.lock();
	log_stream << message << std::endl;
	logMutex.unlock();
}

void sniffer::setDevice( std::string device )
{
	snifferData.setDevice( device );
}

std::string sniffer::getDevice()
{
	snifferData.getDevice();
}

/* Sniffing pcap -file */
void* sniffer::offlineSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t* args = (uint8_t*)filterData;

	snifferData.log( "SnifferOffline Started!" ); 
	snifferData.log( "Opening File: " + snifferData.getDevice() );

	// 65535 from pcap man page...
	pcap_t* descr;
	if( snifferData.getDevice() == "any" )
	{
		descr = pcap_open_live( "any", 65535, 1, -1, errbuf );
	}
	else
	{
		descr = pcap_open_offline( snifferData.getDevice().c_str(), errbuf );
	}
	if ( descr == NULL )
	{
		snifferData.log( (std::string)"SnifferOffline ERROR: " + (std::string)errbuf );
		std::cerr << "SnifferOffline ERROR: " << errbuf << std::endl;
		exit(-1);
	}

	int err = -2;//this is the return value of pcap_loop if stoped with pcap_breakloop()

	filterData->setPcapPointer( descr );

	while( err == -2 )
	{
		snifferData.log( "Sniffer processing packets" );
		err = pcap_loop( descr, -1, my_callback, args );
		snifferData.log( "Sniffer had to stop processing packets" );
		usleep(1);
	}

	snifferData.log( "SnifferOffline Stopping!" );
	pthread_exit(NULL);
}

/*pcap sniffer*/
void* sniffer::devSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t* args = (uint8_t*)filterData;
	snifferData.log( "Sniffer Started!" ); 
	snifferData.log( "Opening Device: " + snifferData.getDevice() );

	// 65535 from pcap man page...
	pcap_t* descr;
	if( snifferData.getDevice() == "any" )
	{
		descr = pcap_open_live( "any", 65535, 1, -1, errbuf );
	}
	else
	{
		//descr = pcap_open_live( snifferData.getDevice().c_str(), 65535, 1, -1, errbuf );
		descr = pcap_open_live( snifferData.getDevice().c_str(), 500, 1, 40, errbuf );
	}
	if ( descr == NULL )
	{
		snifferData.log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
		std::cerr << "Sniffer ERROR: " << errbuf << std::endl;
		exit(-1);
	}

	int err = -2;//this is the return value of pcap_loop if stoped with pcap_breakloop()

	filterData->setPcapPointer( descr );

	while( err == -2 )
	{
		snifferData.log( "Sniffer processing packets" );
		err = pcap_loop( descr, -1, my_callback, args );
		snifferData.log( "Sniffer had to stop processing packets" );
		usleep(1);
	}

	snifferData.log( "Sniffer Stopping!" );
	pthread_exit(NULL);
}

void sniffer::printDevices()
{
	pcap_if_t *alldevs;
	char errbuf[PCAP_ERRBUF_SIZE+1];
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
		exit(1);
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

