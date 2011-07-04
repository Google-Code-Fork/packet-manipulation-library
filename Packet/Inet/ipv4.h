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

/** \file ipv4.h
 * This is the declaration for the class IPv4
 */

/** \class IPv4
 * This class is used in conjunction with Packet for handling IPv4
 *
 */



#ifndef IP_H 
#define IP_H

#include <string>
#include <netinet/in.h>
#include "inetData.h"
#include "../encapsulateable.h"
#include <stdint.h>
#include "ipv4address.h"

/*** Structure of an internet header, naked of options.
 *
 * Taken from tcpdump source (thanks tcpdump people).
 *
 * Used internally to the IPv4 class
 */

typedef struct IPv4Header
{
	u_int8_t  ip_vhl;   //!< header length, version 
	#define IP_V(ip)  (((ip)->ip_vhl & 0xf0) >> 4)
	#define IP_HL(ip) ((ip)->ip_vhl & 0x0f)
	u_int8_t  ip_tos;   //!< type of service 
	u_int16_t ip_len;   //!< total length 
	u_int16_t ip_id;    //!< identification 
	u_int16_t ip_off;   //!<fragment offset field 
	#define IP_DF 0x4000      //!< dont fragment flag 
	#define IP_MF 0x2000      //!< more fragments flag 
	#define IP_OFFMASK 0x1fff   //!< mask for fragmenting bits 
	u_int8_t  ip_ttl;   //!< time to live 
	u_int8_t  ip_p;   //!< protocol 
	u_int16_t ip_sum;   //!< checksum 
	struct  in_addr ip_src,ip_dst;  //!< source and dest address 
}IPv4Header;

namespace ipProtocol
{
  //! \namespace ipProtocols
  //!Constants for the protocols above IP
    const uint8_t IP = 0;	   //!< Dummy protocol for TCP.  
    const uint8_t HOPOPTS = 0;   //!< IPv6 Hop-by-Hop options.  
    const uint8_t ICMP = 1;	   //!< Internet Control Message Protocol.  
    const uint8_t IGMP = 2;	   //!< Internet Group Management Protocol. 
    const uint8_t IPIP = 4;	   //!< IPIP tunnels (older KA9Q tunnels use 94).  
    const uint8_t TCP = 6;	   //!< Transmission Control Protocol.  
    const uint8_t EGP = 8;	   //!< Exterior Gateway Protocol.  
    const uint8_t PUP = 12;	   //!< PUP protocol.  
    const uint8_t UDP = 17;	   //!< User Datagram Protocol.  
    const uint8_t IDP = 22;	   //!< XNS IDP protocol.  
    const uint8_t TP = 29;	   //!< SO Transport Protocol Class 4.  
    const uint8_t IPV6 = 41;     //!< IPv6 header.  
    const uint8_t ROUTING = 43;  //!< IPv6 routing header.  
    const uint8_t FRAGMENT = 44; //!< IPv6 fragmentation header.  
    const uint8_t RSVP = 46;	   //!< Reservation Protocol.  
    const uint8_t GRE = 47;	   //!< General Routing Encapsulation.  
    const uint8_t ESP = 50;      //!< encapsulating security payload.  
    const uint8_t AH = 51;       //!< authentication header.  
    const uint8_t ICMPV6 = 58;   //!< ICMPv6.  
    const uint8_t NONE = 59;     //!< IPv6 no next header.  
    const uint8_t DSTOPTS = 60;  //!< IPv6 destination options.  
    const uint8_t MTP = 92;	   //!< Multicast Transport Protocol.  
    const uint8_t ENCAP = 98;	   //!< Encapsulation Header.  
    const uint8_t PIM = 103;	   //!< Protocol Independent Multicast.  
    const uint8_t COMP = 108;	   //!< Compression Header Protocol.  
    const uint8_t SCTP = 132;	   //!< Stream Control Transmission Protocol.  
    const uint8_t RAW = 255;	   //!< Raw IP packets.  
}

class IPv4 : public InetData
{
	public:
	  //!Default Constructor
	  IPv4();
	  //!Constructs a IPv4 object from a buffer
	  IPv4( const uint8_t *packet, int size );
	  //!Copy constructor
	  IPv4( const IPv4 &n);
	  //!Equality operator
	  IPv4& operator =( const IPv4 &n );
	  //!Destructor
	  ~IPv4();

	  //!Returns the version of IP
	  uint8_t version() const;
	  //!Allows the user to set the version number
	  //!If the user doesn't set this to 4 then it doesn't make much sense
	  //!unless they are trying to create a malformed packet.
	  void setVersion( uint8_t );
	  //!Returns the length of the IP header.
	  uint8_t headerLength() const;
	  //!Sets the length of the header
	  void setHeaderLength( uint8_t );
	  //!returns the total length field
	  uint16_t totalLength() const;
	  //!Sets the total length field 
	  void setTotalLength( uint16_t );
	  //!returns the identification field
	  uint16_t identification() const;
	  //!sets the identification field
	  void setIdentification( uint16_t );
	  //!Returns flag (true|false)
	  bool dontFragment() const;
	  //!Set flag (true|false)
	  void setDontFragment( bool );
	  //!Set flag true
	  void setDontFragment( ); // == setFlagsNoFragment( true );
	  //!Returns flag (true|false)
	  bool moreFragments() const;
	  //!Set flag (true|false)
	  void setMoreFragments( bool );
	  //!Set flag true
	  void setMoreFragments( ); // == setFlagsMoreFragments( true );
	  //!returns the fragment offset field
	  uint16_t fragmentOffset() const;
	  //!sets the fragment offset field
	  void setFragmentOffset( uint16_t );
	  //!Returns the ttl value of the header
	  uint8_t ttl() const;
	  //!Sets the TTL value of the header
	  void setTtl( uint8_t );
	  //!Returns the value of the upper level protocol
	  //!Protocols are defined in the ipProtocols namespace
	  uint8_t protocol() const;
	  //!Sets the value of the upper level protocol
	  //!Protocols are defined in the ipProtocols namespace
	  void setProtocol( uint8_t ); 
	  //!Returns the checksum
	  uint16_t checksum() const;
	  //!Sets the checksum field
	  void setChecksum( uint16_t );
		//!Calculates a valid checksum
		void calculateChecksum();
	  //!returns the sources ip
	  uint32_t sourceAddress() const;
	  //!Sets the source IP
    void setSourceAddress( const IPv4Address &ip );
	  //!returns the destination IP.
	  uint32_t destinationAddress()const;
	  //!sets the destination IP.
    void setDestinationAddress( const IPv4Address &ip );
	  //!Returns a packet buffer suitable for use in other libraries
	  PacketBuffer makePacket() const;
	  //!Returns the number of bytes in the IP header
	  int size() const;
	  //!Returns true this is IP! Overloaded from InetData so we can tell we
	  //have an IP header in the Packet
	  bool isIPv4() const {return true;}

	private:
	  //!internal data
	  IPv4Header *header_;
};

#endif 
