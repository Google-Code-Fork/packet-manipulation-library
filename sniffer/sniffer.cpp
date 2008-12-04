
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
#include"../common/parseCommas.h"

std::ofstream sniffer::log_stream(logFile.c_str(), std::ios::out|std::ios::app);
const std::string sniffer::logFile = "./sniffer.log";

sniffer::sniffer():snifferData( coutMutex, logMutex, &log_stream )
{
	filterData = new FilterData ( coutMutex, logMutex, &log_stream );
	inPcapFile_ = std::string("");
	outPcapFile_ = std::string("");
}

Packet sniffer::popPacket()
{
	return filterData->popPacket();
}

void sniffer::setInputPcapFile(std::string pcapFile)
{
	inPcapFile_ = pcapFile;
}

std::string sniffer::getInputPcapFile( )
{
	return inPcapFile_;
}

void sniffer::setOutPcapFile(std::string pcapFile)
{
	outPcapFile_ = pcapFile;
}

std::string sniffer::getOutputPcapFile( )
{
	return outPcapFile_;
}

void sniffer::setFilter(std::string filter)
{
	filter_ = filter;
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

void* run_sniffer(void* data)
{
	sniffer *tempSniffer = (sniffer*) data;
	tempSniffer->packetSniffer();
}

void* sniffer::packetSniffer()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	uint8_t* args = (uint8_t*)filterData;

	snifferData.log( "SnifferOffline Started!" ); 
	snifferData.log( "Opening File: " + snifferData.getDevice() );

	// 65535 from pcap man page...
	pcap_t* pcap_ptr;
	if(inPcapFile_.size())
		pcap_ptr = pcap_open_offline( inPcapFile_.c_str(), errbuf );
	else
	{
		if( snifferData.getDevice() == "any" )
			pcap_ptr = pcap_open_live( "any", 65535, 1, -1, errbuf );
		else
			pcap_ptr = pcap_open_live( snifferData.getDevice().c_str(), 500, 1, 40, errbuf );
	}

	if ( pcap_ptr == NULL )
	{
		snifferData.log( (std::string)"Sniffer ERROR: " + (std::string)errbuf );
		std::cerr << "Sniffer ERROR: " << errbuf << std::endl;
		exit(-1);
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
			exit(1);
		}

		//set the filter
		if(pcap_setfilter(pcap_ptr, &fcode)<0)
		{
			fprintf(stderr,"\nError setting the filter\n");
			exit(1);
		}
	}

	if (outPcapFile_.size() != 0)
	{
		pcap_dumper_t *dumpfile; 
		struct pcap_pkthdr *header;
		const u_char *pkt_data;
		dumpfile= pcap_dump_open(pcap_ptr, outPcapFile_.c_str());
		//dumpfile= pcap_dump_open(fp, "-");

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

	snifferData.log( "SnifferOffline Stopping!" );
//	pthread_exit(NULL);
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

