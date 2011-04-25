/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra, Mike Kozma
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

/*
 * \file ipv6.h
 * This is the declaration for the class IPv6
*/

/*
 * \class IPv6
 * This class is used in conjunction with Packet for handling IPv6
*/

#ifndef IPv6_H
#define IPv6_H

#include <string>
#include <netinet/in.h>
#include "inetData.h"
#include "../encapsulateable.h"
#include <vector>
#include "ipv6Address.h"

typedef struct IPv6Header
{
	u_int32_t ip_vtf;		//!< version, traffic class, flow label
	#define IP_VER(ip) (((ip)->ip_vtf & 0xf0000000 ) >> 28 )
	#define IP_TC(ip) (((ip)->ip_vtf & 0x0ff00000 ) >> 20 )
	#define IP_FL(ip) (((ip)->ip_vtf & 0x000fffff ))
	u_int16_t ip_len;		//!< payload length
	u_int8_t ip_nh;			//!< next header
	u_int8_t ip_hl;			//!< hop limit
//	std::vector< u_int8 > sourceAdd(16);	//!< source address
//	std::vector< u_int8 > destAdd(16);		//!< destination address
	u_int8_t srcAddr[IPv6Address::IPv6AddressSize];	//!< src IPv6 address-16Bytes
	u_int8_t dstAddr[IPv6Address::IPv6AddressSize];	//!< dst IPv6 address-16Bytes
}IPv6Header;

class IPv6 : public InetData
{
	public:
		//!Default Constructor
		IPv6();
		//!Constructs a IPv6 object from a buffer
		IPv6( const uint8_t *packet, int size );
		//!Copy constructor
		IPv6( const IPv6 &n );
		//!Equality operator
		IPv6& operator = ( const IPv6 &n );
		//!Destructor
		~IPv6();

		//!Returns the Version field
		uint32_t version() const;
		//!Allow the user to set the version number
		//!If the user doesn't set this to 6 then it doesn't make much sense
		//!unless they are trying to create a malformed packet.
		void setVersion( uint32_t );
		//!Returns the Traffic Class field
		uint32_t trafficClass() const;
		//!Sets the Traffic Class field
		void setTrafficClass( uint32_t );
		//!Return the Flow Label field
		uint32_t flowLabel() const;
		//!Sets the Flow Label field
		void setFlowLabel( uint32_t );
		//!Return the Payload Length field
		uint16_t payloadLength() const;
		//!Sets the Payload Length field
		void setPayloadLength( uint16_t );
		//!Return the Next Header field
		uint8_t nextHeader() const;
		//!Sets the Next Header field
		void setNextHeader( uint8_t );
		//!Return the Hop Limit field
		uint8_t hopLimit() const;
		//!Sets the Hop Limit field
		void setHopLimit( uint8_t );

		//!Return the source IPv6 address in the IP header
		IPv6Address sourceIP();
		//!Sets the source IPv6 address in the IP header to v6
		void setSourceIP( IPv6Address v6 );
		//!Return the destination IPv6 address in the IP header
		IPv6Address destinationIP();
		//!Set the destination IPv6 address in the IP header to v6
		void setDestinationIP( IPv6Address v6 );
		//!Returns true this is IP! Overloaded from InetData so we can tell we have
		//an IP header in the packet
		bool isIPv6() const {return true;}

	private:
		//!Internal data for IPv6
		IPv6Header *header_;
};

#endif
