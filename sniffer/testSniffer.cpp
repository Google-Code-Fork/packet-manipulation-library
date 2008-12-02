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


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "sniffer.h"
#include "snifferData.h"
//#include "constants.h"
#include "filterData.h"
#include "../common/commandLineParser.h"
#include "../common/parseCommas.h"
#include "../common/threads.h"

//void log( std::string );
std::string parser(int argc, char *argv[], std::string option);
void printHelp();

namespace inav {
	const std::string logFile = "./inavd.log";
	bool DEBUG=false;

	/*Globals and not Constants */
	Mutex coutMutex;
	Mutex logMutex;
	std::ofstream log (logFile.c_str(), std::ios::out|std::ios::app);
}

int main(int argc, char *argv[])
{
	std::cout << "PACMAN v" << "0.0.0.0.1" << std::endl;
	std::vector<Thread *> threads;
	int returnCode;
	sniffer sniffer_instance;

	//Print Help
	std::string parsedString = parser( argc, argv, "-h" );
	if( parsedString.size() > 0 )
		printHelp();
	parsedString = parser( argc, argv, "--help" );
	if( parsedString.size() > 0 )
		printHelp();

	//Check for debug
	parsedString = parser( argc, argv, "-vv" );
	if( parsedString.size() > 0 )
		sniffer_instance.setDebug(true);


	//check log file
	if (!inav::log)
	{
		std::cerr << "Unable to write to log file: " << inav::logFile << std::endl;
		exit(-1);
	}
	sniffer_instance.log("INAV starting up!");

	//check command line options
	//check if we should print out pcap capabile devices
	parsedString = parser( argc, argv, "-ls" );
	if ( parsedString == "set" )
	{
		sniffer_instance.log( "Server started with -ls option printing devices and halting..." );
		sniffer_instance.printDevices();
		exit(-1);
	}

	std::string device = parser( argc, argv, "-i" );
	if( device == "set" )
	{
			sniffer_instance.log( "WARNING: device flag given but no device specified!" );
			exit( -1 );
	}
	std::cout << "Device(s) set to " <<   device << std::endl;
	sniffer_instance.log( "Device(s) set to " + device );
	std::vector< std::string > devices;
	if( device.size() != 0 )
		devices = parseCommas( device );

	//Setup pcap file input
	std::string file = parser( argc, argv, "-f" );
	if( file == "set" )
	{
			sniffer_instance.log( "WARNING: input selected as pcap file with no file specified. CANNOT CONTINUE" );
			exit( -1 );
	}
	std::cout << "File(s) set to " << file << std::endl;
	sniffer_instance.log( "File(s) set to " + file );
	std::vector< std::string > files;
	if( file.size() != 0 )
		files = parseCommas( file );

	std::string cvsFile = parser( argc, argv, "-c" );
	if( cvsFile == "set" )
	{
		sniffer_instance.log( "WARNING: input for cvs files is blank. CANNOT CONTINUE" );
		exit( -1 );
	}
	std::cout << "CVSFile(s) Set To " << cvsFile << std::endl;
	sniffer_instance.log( "CVSFILE(s) Set To " + cvsFile );
  std::vector< std::string > cvsFiles;
	if( cvsFile.size() != 0 ) 
		cvsFiles = parseCommas( cvsFile );

	

	//Creating different datastructures
	SnifferData snifferTemplate( inav::coutMutex, inav::logMutex, &inav::log );
	snifferTemplate.setDevice( device );
	FilterData filterData( inav::coutMutex, inav::logMutex, &inav::log );

	sniffer_instance.log( "Creating Sniffer Thread(s)" );
	std::vector< std::string >::iterator sitr;
	for( sitr = devices.begin(); sitr != devices.end(); ++sitr )
	{
		//Set up sniffing threads
		sniffer tempSniffer;
		tempSniffer.setDevice( *sitr );
		Thread* thread = new Thread( run_devSniffer );
		thread->start( (void *) &tempSniffer );
		threads.push_back( thread );
	}

	sniffer_instance.log( "Creating Sniffer Offline Thread(s)" );
	for( sitr = files.begin(); sitr != files.end(); ++sitr )
	{
		//Set up sniffing threads
		sniffer tempSniffer;
		tempSniffer.setDevice( *sitr );
		Thread* thread = new Thread( run_offlineSniffer );
		thread->start( (void*) &tempSniffer );
		threads.push_back( thread );
	}

/*	sniffer_instance.log( "Creating cvsFile Input Thread(s) " );
	for( sitr = cvsFiles.begin(); sitr != cvsFiles.end(); ++sitr )
	{
		//Set up pcap file threads
		SnifferDataHolder snifferDataHolder;
		SnifferData *snifferData = new SnifferData( snifferTemplate );
		snifferData->setDevice( *sitr );
		snifferDataHolder.snifferData = snifferData;
		snifferDataHolder.filterData = &filterData;

		Thread* thread = new Thread( cvsSniffer );
		thread->start( (void*)&snifferDataHolder );
		threads.push_back( thread );
	}*/


	//Set up Bandwidth Monitor Thread
	


	//Wait for threads to exit
	//(void*) 
	std::vector<Thread*>::iterator itr;
	for( itr = threads.begin(); itr != threads.end(); ++itr )
	{
		sniffer_instance.log( "Deleting Thread... " );
		(*itr)->join();
	}
	sniffer_instance.log( "INAV server halting!" );
	return 0;
}

/*void log( std::string message )
{
	inav::logMutex.lock();
	inav::log << message << std::endl;
	inav::logMutex.unlock();
}*/

void printHelp()
{
	std::cout << "INAV Copyright © 2007 Jeff Scaparra, Nathan Robinson" << std::endl;
	std::cout << "This program is free software: you can redistribute it and/or modify" << std::endl;
	std::cout << "it under the terms of the GNU General Public License as published by" << std::endl;
	std::cout << "the Free Software Foundation, either version 3 of the License, or" << std::endl;
	std::cout << "(at your option) any later version." << std::endl;
	std::cout << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "-h" << std::endl;
	std::cout << "--help \t\t This help menu. " << std::endl;
	std::cout << "-vv    \t\t Extra verbosity." << std::endl;
	std::cout << "-v     \t\t Display version" << std::endl;
	std::cout << "-ls    \t\t List available devices" << std::endl;
	std::cout << "-i <interfaces>\t specify interface or multiple eth0,eth1,eth2" << std::endl;
	std::cout << "-f <pcapfiles>\t List pcap files to use as input" << std::endl;
	std::cout << "-c <cvsfiles>\t List of cvs files to use as input" << std::endl;
	std::cout << "-s <usec>\t Nano seconds to wait before loading in next line of a cvs file" << std::endl;
	std::cout << "-p <portNum>\t specifty port number to listen on" << std::endl;
	std::cout << "--debug \t starts the debug thread." << std::endl;
	exit( 0 );
}

