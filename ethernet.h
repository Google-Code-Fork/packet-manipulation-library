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


#ifndef ETHERNET_H
#define ETHERNET_H

#include <string>
#include <pcap.h>
#include <net/ethernet.h>

struct vlanTag {
	uint16_t vlan;
	#define vlanPriority( vlanTag ) (((vlanTag)->vlan & 0x0007 ))
	#define vlanCFI( vlanTag ) (((vlanTag)->vlan & 0x0008 ) >> 3 )
	#define vlanID( vlanTag ) (((vlanTag)->vlan & 0xFFF0 ) >> 4 )
	uint16_t type;
};

class Ethernet
{
	public:
		Ethernet();
		Ethernet( const uint8_t *packet );
		Ethernet( const Ethernet& n );
		Ethernet& operator =( const Ethernet &n);
		~Ethernet();

		std::string getDestinationMAC();
		void setDestinationMAC( std::string );
		std::string getSourceMAC();
		void setSourceMAC( std::string );
		uint16_t getType();
		void setType( uint16_t );
		uint16_t getDot1QType();
		void setDot1QType( uint16_t );
		int getSize();

	private:
		struct ether_header* header_;
		struct vlanTag* vlanTag_;
};




#endif 
