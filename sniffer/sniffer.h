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
#include "device.h"

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture );
void* run_sniffer(void* data);

class sniffer : public Thread
{
	private:
		Mutex coutMutex;
		Mutex logMutex;
		std::string filter_;
		FilterData *filterData;
		SnifferData snifferData;
		static const std::string logFile;
		static std::ofstream log_stream;
		Device inDev_;
		Device outDev_;

	public:
		sniffer();
		void *packetSniffer();
		void setDevice( std::string device );
		std::string getDevice();
		void setFilter(std::string filter);
		void setOutPcapFile(std::string);
		std::string getOutputDevice( );
		void setInputPcapFile(std::string);
		std::string getInputDevice();
		Packet popPacket();
		void log( std::string );
		void start( );
		void printDevices();
		std::string iptos(u_long in);
		~sniffer(){ delete filterData; }
};

