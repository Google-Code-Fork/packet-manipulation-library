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


#include "snifferData.h"
#include "filterData.h"

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture );
void* run_sniffer(void* data);

class sniffer
{
	private:
		static const std::string logFile;
		bool DEBUG;

		static std::ofstream log_stream;
		Mutex coutMutex;
		Mutex logMutex;
		std::string outPcapFile_;
		std::string inPcapFile_;
		std::string filter_;

		FilterData *filterData;
		SnifferData snifferData;

	public:
		sniffer();
		void printDevices();
		static std::string iptos(u_long in);
		void setDevice( std::string device );
		std::string getDevice();
		void log( std::string );
		void setDebug(bool value);
		void *packetSniffer();
		Packet popPacket();
		void setOutPcapFile(std::string);
		std::string getOutputPcapFile( );
		void setInputPcapFile(std::string);
		std::string getInputPcapFile();
		void setFilter(std::string filter);
};

