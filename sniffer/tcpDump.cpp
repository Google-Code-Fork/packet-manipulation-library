
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "sniffer.h"
#include "snifferData.h"
#include "filterData.h"
#include "../common/threads.h"
#include "options.h"


int main(int argc, char *argv[])
{
	std::cout << "PACMAN v" << "0.0.0.0.1" << std::endl;
	options tcpOptions;
	tcpOptions.get_options(argc, argv);
	tcpOptions.print_options();

	sniffer mySniffer;

	mySniffer.log("tcpdump starting up!");

	//check if we should print out pcap capabile devices
	if ( tcpOptions.is_ls )
	{
		mySniffer.log( "Server started with -ls option printing devices and halting..." );
		mySniffer.printDevices();
		exit(-1);
	}

	if(tcpOptions.is_filter)
		mySniffer.setFilter(std::string(tcpOptions.get_filter()));
	if(tcpOptions.is_pcapDev)
		mySniffer.setDevice(std::string(tcpOptions.get_pcapDev()));
	else if(tcpOptions.is_inputPcapFile)
		mySniffer.setInputPcapFile(std::string(tcpOptions.get_inputPcapFile()));
	if(tcpOptions.is_outputPcapFile)
		mySniffer.setOutPcapFile(std::string(tcpOptions.get_outputPcapFile()));
	
	mySniffer.start();
	int count = 0;
	while(count++ < 10)
	{
		Packet p = mySniffer.popPacket();
		std::cerr<<"Packet count:"<<count<<std::endl;
		
	}
	std::cerr << "Done" << std::endl;
	mySniffer.stop();	
	mySniffer.log( "tcpdump halting!" );
	return 0;
}

