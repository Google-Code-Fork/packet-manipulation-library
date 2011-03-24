/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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


#ifndef ARP_H 
#define ARP_H

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <stdint.h>
#include "../packetBuffer.h"
#include "appData.h"

typedef struct my_arp {
	uint16_t hardwareType;
	uint16_t protocolType;
	uint8_t hardwareSize;
	uint8_t protocolSize;
	uint16_t opcode;
} ARPHeader;

namespace arpopcode
{
  const uint16_t request = 1;
  const uint16_t response = 2; 
}

namespace protocoltype
{
	const uint16_t IP = 0x0800;
}

namespace hardwaretype
{
	const uint16_t ETHERNET = 0x0001;
}

namespace protocolsize
{
	const uint8_t IP = 4;
}

namespace hardwaresize
{
	const uint8_t ETHERNET = 6;
}

class Arp : public AppData
{
  public:
    Arp( );
		Arp( const uint8_t *data, int size );
    Arp( const std::vector<uint8_t> packet );
    Arp( const Arp &n );
    Arp& operator=( const Arp &n );
		Arp( const PacketBuffer &packet );
    virtual ~Arp( );

		uint16_t hardwareType() const;
		void setHardwareType( const uint16_t &hardwareType );
		uint16_t protocolType() const;
		void setProtocolType( const uint16_t &protocolType );
		uint8_t hardwareSize() const;
		void setHardwareSize( const uint8_t &size );
		uint8_t protocolSize() const;
		void setProtocolSize( const uint8_t &size );
		uint16_t opcode() const; 
		void setOpcode( const uint16_t &opcode );
		PacketBuffer senderMacAddress() const;
		void setSenderMacAddress( const PacketBuffer &pb );
		PacketBuffer senderIPAddress() const;
		void setSenderIPAddress( const PacketBuffer &pb );
		PacketBuffer targetMacAddress() const;
		void setTargetMacAddress( const PacketBuffer &pb );
		PacketBuffer targetIPAddress( ) const;
		void setTargetIPAddress( const PacketBuffer &pb );

		std::vector< uint8_t > data() const;
		PacketBuffer makePacket() const;

		bool isARP() const { return true; }


	private:
		void init( const std::vector< uint8_t > &datav );
  private:
    ARPHeader header_;
		PacketBuffer senderMacAddress_;
		PacketBuffer senderIPAddress_;
		PacketBuffer targetMacAddress_;
		PacketBuffer targetIPAddress_;
};

#endif
