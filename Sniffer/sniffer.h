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

typedef struct threadData
{
	FilterData* filterData;
	pcap_t* pcapPointer;
}ThreadData;

class Sniffer 
{
	public:
		Sniffer();
		void *packetSniffer();
		void setInputDevice( const std::string &device );
		void setInputDevices( const std::vector< std::string > &devices );
		void addInputDevice( const std::string &device );
		void clearInputDevices( );
		void setFilter( const std::string &filter);
		void setOutPcapFile( const std::string &file);
		std::string outputDevice( ) const;
		void setInputPcapFile(const std::string &file);
		void setInputPcapFiles(const std::vector< std::string > &files );
		void setSnapLength( const uint32_t &length );
		uint32_t snapLength() const;
		std::vector< std::string > inputDevices() const;
		Packet popPacket();
		bool sniffing() const;
		void log( const std::string &logfile );
		void start( );
		void stop( );
		void restart( );
		void printDevices() const;
		std::vector< std::string > availableDevices() const;
		//std::string iptos(u_long in); //?
		~Sniffer(){ delete filterData_; }
	
	
	private:
		std::vector< Thread > threads_;
		mutable Mutex coutMutex_;
		mutable Mutex logMutex_;
		std::string filter_;
		FilterData *filterData_;
		SnifferData snifferData_;
		static const std::string logFile_;
		static std::ofstream log_stream_;
		std::vector< Device > snifferDevices_;
		Device outDev_;

		mutable Mutex sniffingMutex_;
		bool sniffing_;
		
		uint32_t snapLength_;
		static const uint32_t DEFAULT_SNAP_LENGTH;
		
		uint32_t numberOfRunningThreads_;
		mutable Mutex threadNumMutex_;

};

