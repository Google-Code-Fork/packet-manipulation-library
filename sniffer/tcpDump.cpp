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


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "sniffer.h"
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

