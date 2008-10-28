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
//#include<netinet/ip.h>
#include<algorithm>
#include<stdexcept>
#include"sniffer.h"
#include"snifferData.h"
#include"filterData.h"
#include"packet.h"
#include"../common/constants.h"
#include"../common/parseCommas.h"

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture )
{
	FilterData* filterData = (FilterData*)args;
	if( filterData->size() >= sniff::MAX_PACKETS_QUEUED )
	{
		pcap_breakloop( filterData->getPcapPointer() );
	}
	try
	{
	  Packet packet( packetCapture, pkthdr );
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

void *snifferOffline( void *data )
{
	char errbuf[PCAP_ERRBUF_SIZE];

	SnifferData *snifferData = ((SnifferDataHolder*)data)->snifferData;
	FilterData *filterData= ((SnifferDataHolder*)data)->filterData;
	uint8_t* args = (uint8_t*)filterData;
	if ( snifferData == NULL )
	{
		std::cerr << "SnifferOffline ERROR: snifferData == NULL" << std::endl;
		exit(-1);
	}

	if ( filterData == NULL )
	{
		std::cerr << "SnifferOffline ERROR: filterData == NULL" << std::endl;
		exit(-1);
	}

	snifferData->log( "SnifferOffline Started!" ); 
	snifferData->log( "Opening File: " + snifferData->getDevice() );

	// 65535 from pcap man page...
	pcap_t* descr;
	if( snifferData->getDevice() == "any" )
	{
		descr = pcap_open_live( "any", 65535, 1, -1, errbuf );
	}
	else
	{
		descr = pcap_open_offline( snifferData->getDevice().c_str(), errbuf );
	}
	if ( descr == NULL )
	{
		snifferData->log( (std::string)"SnifferOffline ERROR: " + (std::string)errbuf );
		std::cerr << "SnifferOffline ERROR: " << errbuf << std::endl;
		exit(-1);
	}

	int err = -2;//this is the return value of pcap_loop if stoped with pcap_breakloop()

	filterData->setPcapPointer( descr );

	while( err == -2 )
	{
		snifferData->log( "Sniffer processing packets" );
		err = pcap_loop( descr, -1, my_callback, args );
		snifferData->log( "Sniffer had to stop processing packets" );
		usleep(1);
	}
	
	snifferData->log( "SnifferOffline Stopping!" );
	pthread_exit(NULL);
}

/*cvsSniffer*/
void *cvsSniffer( void *data)
{
	SnifferData *snifferData = ((SnifferDataHolder*)data)->snifferData;
	FilterData *filterData= ((SnifferDataHolder*)data)->filterData;
	uint8_t* args = (uint8_t*)filterData;
	if ( snifferData == NULL )
	{
		std::cerr << "cvsSniffer() ERROR: snifferData == NULL" << std::endl;
		exit(-1);
	}

	if ( filterData == NULL )
	{
		std::cerr << "cvsSniffer() ERROR: filterData == NULL" << std::endl;
		exit(-1);
	}

	try
	{
		snifferData->log( "cvsSniffer Started!" ); 
		snifferData->log( "Opening File: " + snifferData->getDevice() );
	}
	catch( ... )
	{
	}

	std::ifstream file(snifferData->getDevice().c_str() );
	std::string line;
	std::cerr << "CVSSNIFFER" << std::endl;

	try
	{
		file.exceptions( std::ios::failbit | std::ios::badbit );
		std::cerr << "Reading file" << std::endl;
		std::getline( file, line );
		std::vector< std::string > scheme = parseCommas( line );
		std::vector< std::string >::iterator itr;
		for ( itr = scheme.begin(); itr != scheme.end(); ++itr )
		{
			std::transform( (*itr).begin(), (*itr).end(), (*itr).begin(), toupper );
			if( "SIP" != (*itr) && 
					"SPORT" != (*itr) &&
					"DIP" != (*itr) && 
					"DPORT" != (*itr) &&
					"PROTOCOL" != (*itr) &&
					"TIME" != (*itr) &&
					"SIZE" != (*itr) &&
					"SENSOR" != (*itr) )
			{
				(*itr) = "FILL"; //i.e. feild not supported
			}
		}

		while ( true ) //until throws exception (i.e. EOF)
		{
			std::getline( file, line );
			std::vector< std::string > data = parseCommas( line );
			std::vector< std::string >::iterator itr;

			std::cerr << "Data.size() = " << data.size() << std::endl;
			Packet packet;
			uint16_t sport = 0;
			uint16_t dport = 0;
			uint32_t sip = 0;
			uint32_t dip = 0;
			uint8_t protocol = 0;
			int count = 0;
			try 
			{
				for ( itr = data.begin(); itr != data.end(); ++itr )
				{
					if( scheme.at( count ) == "SIP" )
					{
						std::cout << "SIP: " << *itr << std::endl;
						if( !inet_aton( (*itr).c_str(), (struct in_addr*) &sip ) )
						{ 
							throw std::runtime_error( "Invalid IP in SIP" );
						}
					}
					else if( scheme.at( count ) == "DIP" )
					{
						if( ! inet_aton( (*itr).c_str(), (struct in_addr*) &dip ) )
						{
							throw std::runtime_error( "Invalid IP in DIP" );
						} 
					}
					else if( scheme.at( count ) == "SPORT" )
					{
						std::istringstream stream(*itr);
						stream >> sport;
					}
					else if( scheme.at( count ) == "DPORT" )
					{
						std::istringstream stream( *itr );
						stream >> dport;
					}
					else if( scheme.at( count ) == "PROTOCOL" )
					{
						std::transform( (*itr).begin(), (*itr).end(), (*itr).begin(), toupper );
						if( *itr == "TCP" )
						{
							protocol = net::TCP;
						}
						else if( *itr == "UDP" )
						{
							protocol = net::UDP;
							packet.isUDP( true );
						}
						else if( *itr == "ICMP" )
						{
							packet.isICMP( true );
							protocol = net::ICMP;
						}
						else
						{
							protocol = 0;
						}
					}
					count++;
				}
			}
			catch( std::range_error &error )
			{
				count = 0; 
				continue;
			}
			catch( std::out_of_range &e )
			{
				count = 0;
				continue;
			}


			if( protocol == net::TCP )
			{
				packet.isTCP( true );
				packet.setTCPSourcePort( sport );
				packet.setTCPDestinationPort( dport );
				packet.setSourceAddress( sip );
				packet.setDestinationAddress( dip );
				packet.setProtocol( protocol );
			}
			else if( protocol == net::UDP )
			{
				packet.isUDP( true );
				packet.setUDPSourcePort( sport );
				packet.setUDPDestinationPort( dport );
				packet.setSourceAddress( sip );
				packet.setDestinationAddress( dip );
				packet.setProtocol( protocol );
			}
			else if( protocol == net::ICMP )
			{
				packet.isICMP( true );
				packet.setSourceAddress( sip );
				packet.setDestinationAddress( dip );
				packet.setProtocol( protocol );
			}
			else 
			{
				packet.isIP( true );
				packet.setSourceAddress( sip );
				packet.setDestinationAddress( dip );
				packet.setProtocol( protocol );
			}
			std::cerr << "PUSHING PACKET" << std::endl;
			filterData->pushPacket( packet );
			usleep( 10 );
		}
	}
	catch ( const std::ios_base::failure& error )
	{
		//prolly an eof
		std::cerr << "EOF" << std::endl;
	}
	catch ( const std::exception& error )
	{
		std::cerr << "UNKNOWN: " << error.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "Caught unknown exception" << std::endl;
	}

	pthread_exit(NULL);

}

/*pcap sniffer*/
void *sniffer(void *data )
{
	char errbuf[PCAP_ERRBUF_SIZE];

	SnifferData *snifferData = ((SnifferDataHolder*)data)->snifferData;
	FilterData *filterData= ((SnifferDataHolder*)data)->filterData;
	uint8_t* args = (uint8_t*)filterData;
	if ( snifferData == NULL )
	{
		std::cerr << "Sniffer ERROR: snifferData == NULL" << std::endl;
		exit(-1);
	}

	if ( filterData == NULL )
	{
		std::cerr << "Sniffer ERROR: filterData == NULL" << std::endl;
		exit(-1);
	}

	snifferData->log( "Sniffer Started!" ); 
	snifferData->log( "Opening Device: " + snifferData->getDevice() );

	// 65535 from pcap man page...
	pcap_t* descr;
	if( snifferData->getDevice() == "any" )
	{
		descr = pcap_open_live( "any", 65535, 1, -1, errbuf );
	}
	else
	{
		//descr = pcap_open_live( snifferData->getDevice().c_str(), 65535, 1, -1, errbuf );
		descr = pcap_open_live( snifferData->getDevice().c_str(), 500, 1, 40, errbuf );
	}
	if ( descr == NULL )
	{
		snifferData->log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
		std::cerr << "Sniffer ERROR: " << errbuf << std::endl;
		exit(-1);
	}

	int err = -2;//this is the return value of pcap_loop if stoped with pcap_breakloop()

	filterData->setPcapPointer( descr );

	while( err == -2 )
	{
		snifferData->log( "Sniffer processing packets" );
		err = pcap_loop( descr, -1, my_callback, args );
		snifferData->log( "Sniffer had to stop processing packets" );
		usleep(1);
	}

	snifferData->log( "Sniffer Stopping!" );
	pthread_exit(NULL);
}

void printDevices()
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



std::string iptos(u_long in)
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

