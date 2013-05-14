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

/** \file icmp.h
 * This is the declaration for the class ICMP 
 */

/** \class ICMP 
 * This class is used in conjunction with Packet for handling ICMP
 *
 */



#ifndef ICMP_H
#define ICMP_H


#include <stdexcept>
#include <netinet/in.h>
#include "../packet.h"
#include "inetData.h"

//! icmp header data for use in the class ICMP
typedef struct icmpHeader 
{
  uint8_t type;
  uint8_t code;
  uint16_t checkSum;
}__attribute__((__packed__)) icmpHeader;

//! icmpRequest data for use in ICMP
typedef struct icmpRequest
{
  uint16_t identifier;
  uint16_t sequence;
} __attribute__((__packed__)) icmpRequest;

namespace icmpTypes
{
	const uint8_t ICMP_ECHO_REPLY = 0; // [RFC792]
  const uint8_t ICMP_UNASSIGNED_1 = 1; //     [JBP]
  const uint8_t ICMP_UNASSIGNED_2 = 2; //     [JBP]
  const uint8_t ICMP_DESTINATION_UNREACHABLE = 3; // [RFC792]
  const uint8_t ICMP_SOURCE_QUENCH = 4; // [RFC792]
  const uint8_t ICMP_REDIRECT = 5; // [RFC792]
	const uint8_t ICMP_ALTERNATE_HOST_ADDRESS = 6; // [JBP]
	const uint8_t ICMP_UNASSIGNED_7 = 7; //JBP
	const uint8_t ICMP_ECHO_REQUEST = 8; // [RFC792]
	const uint8_t ICMP_ROUTER_ADVERTISEMENT = 9; // [RFC1256]
	const uint8_t ICMP_ROUTER_SELECTION = 10; // [RFC1256]
	const uint8_t ICMP_TIME_OUT = 11; // [RFC792]
	const uint8_t ICMP_PARAMETER_PROBLEM = 12; // [RFC792]
	const uint8_t ICMP_TIMESTAMP = 13; // [RFC792]
	const uint8_t ICMP_TIMESTAMP_REPLY = 14; // [RFC792]
	const uint8_t ICMP_INFORMATION_REQUEST = 15; // [RFC792]
	const uint8_t ICMP_INFORMATION_REPLY = 16; // [RFC792]
	const uint8_t ICMP_ADDRESS_MASK_REQUEST = 17; // [RFC950]
	const uint8_t ICMP_ADDRESS_MASK_REPLY = 18; // [RFC950]
	const uint8_t ICMP_RESERVED_SECURITY = 19; // [Solo]
	//const uint8_t ICMP_RESERVED_ROBUSTNESS = 20 - 29 ; // [ZSu]
	const uint8_t ICMP_TRACEROUTE = 30; // [RFC1393]
	const uint8_t ICMP_DATAGRAM_CONVERSION_ERROR = 31; // [RFC1475]
	const uint8_t ICMP_MOBILE_HOST_REDIRECT = 32; // [David Johnson]
	const uint8_t ICMP_IPv6_WHERE_ARE_YOU = 33; // [Bill Simpson]
	const uint8_t ICMP_IPv6_I_AM_HERE = 34; // [Bill Simpson]
	const uint8_t ICMP_MOBILE_REGISTRATION_REQUEST = 35; // [Bill Simpson]
	const uint8_t ICMP_MOBILE_REGISTRATION_REPLY = 36; // [Bill Simpson]
	const uint8_t ICMP_DOMAIN_NAME_REQUEST = 37; // [Bill Simpson]
}


class Packet;

//!helper function for calculating checksums
uint16_t icmpChecksum (uint16_t * buffer, int numOfBytes );

class ICMP : public InetData
{
  public:
    //!constructor
    ICMP();
    //!destructor
    ~ICMP();
    //!construcot ICMP object from buffer
    ICMP( const uint8_t *packet, const int size );
    //!copy constructor
    ICMP( const ICMP &n );
    //! equality operator
    ICMP& operator= ( const ICMP &n );

    //!Return the ICMP type
    uint8_t type() const;
    
		//!Set the ICMP type
		/*! This can remove information. For example if a icmp header goes from a
		 * type 8 echo request to something else it will lose its request header and 
		 * everything associated with it.
		 */
    void setType(uint8_t type);
   
		//!Return the ICMP code
    uint8_t code() const;
   
		//!set the ICMP code
    void setCode(uint8_t code);
   
		//!return the checksum field
    uint16_t checksum() const;
   
		//!set the checksum
    void setChecksum( uint16_t );

    //!return the length of the header
    int headerLength() const;

    //!if a type 8 icmp request
    uint16_t identifier() const;
   
		//!to set a type 8 icmp request
    void setIdentifier( uint16_t ident );
   
		//!return sequence number
    uint16_t sequenceNum() const;
   
		//!set the squence number
    void setSequenceNum( uint16_t sequence );
   
		//!generate the checksum
    void generateChecksum();

    //!This is for type 11 icmp time-to-live exceeded 
    /*!Returns a Packet object with the orginal content of the the exceeded
    packet.*/
    Packet orginalPacket() const;
    
		//!Returns the size in bytes of the ICMP header
    int size() const;
   
		//!Returns true... overloaded from InetData
    bool isICMP() const { return true; }

		//! Make a PacketBuffer
    PacketBuffer makePacket() const;

  private:
    //!internal data
    icmpHeader *header_;//All icmp packets :)
   
		//!internal data
    icmpRequest *request_; //type 8
   
		//!internal data
    Packet *orginal_; //type 11 copy of orginal packet ip header
};

#endif
