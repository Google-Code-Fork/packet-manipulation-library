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

#include "snifferData.h"
#include "filterData.h"
#include "../Device/device.h"
#include <string>
#include <vector>

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture );
void* run_sniffer(void* data);

class sniffer : public Thread
{
	public:
		sniffer();
		void *packetSniffer();
		void setInputDevice( const std::string &device );
		void setFilter( const std::string &filter);
		void setOutPcapFile( const std::string &file);
		std::string outputDevice( ) const;
		void setInputPcapFile(const std::string &file);
		std::string inputDevice() const;
		Packet popPacket();
		bool sniffing() const;
		void log( const std::string &logfile );
		void start( );
		void printDevices() const;
		std::vector< std::string > availableDevices() const;
		//std::string iptos(u_long in); //?
		~sniffer(){ delete filterData; }
	
	
	private:
		mutable Mutex coutMutex;
		mutable Mutex logMutex;
		std::string filter_;
		FilterData *filterData;
		SnifferData snifferData;
		static const std::string logFile;
		static std::ofstream log_stream;
		Device inDev_;
		Device outDev_;
		mutable Mutex sniffingMutex_;
		bool sniffing_;

};

