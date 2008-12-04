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


#ifndef ICMP_H
#define ICMP_H


#include <stdexcept>
#include <netinet/in.h>
#include "../packet.h"
#include "inetData.h"

typedef struct icmpHeader 
{
	uint8_t type;
	uint8_t code;
	uint16_t checkSum;
} icmpHeader;

typedef struct icmpRequest
{
	uint16_t identifier;
	uint16_t sequence;
}icmpRequest;

class Packet;

//helper function
uint16_t icmpChecksum (uint16_t * buffer, int numOfBytes );

class ICMP : public InetData
{
	public:
		ICMP();
		~ICMP();
		ICMP( const uint8_t *packet, const int size );
		ICMP( const ICMP &n );
		ICMP& operator= ( const ICMP &n );

		uint8_t getType() const;
		void setType(uint8_t type);
		uint8_t getCode() const;
		void setCode(uint8_t code);
		uint16_t getChecksum() const;
		void setChecksum( uint16_t );

		int getHeaderLength() const;

		//type 8 icmp request
		uint16_t getIdentifier() const;
		void setIdentifier( uint16_t ident );
		uint16_t getSequenceNum() const;
		void setSequenceNum( uint16_t sequence );
		void generateChecksum();

		//type 11 icmp time-to-live exceeded 
		Packet getOrginalPacket();

		PacketBuffer make Packet() const;
		int getSize() const;
		bool isICMP() const { return true; }

	private:
		icmpHeader *header_;//All icmp packets :)
		icmpRequest *request_; //type 8
		uint8_t *orginal_; //type 11 copy of orginal packet ip header
};

#endif
