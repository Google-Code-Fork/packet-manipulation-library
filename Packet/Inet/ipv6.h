/*
 * \file ipv6.h
 * This is the declaration for the class IPv6
*/

/*
 * \class IPv6
 * This class is used in conjunction with Packet for handling IPv6
*/

#ifndef IP_H
#define IP_H

#include <string>
#include <netinet/in.h>
#include "inetData.h"
#include "../encapsulateable.h"
#include <vector>

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
	u_int8_t srcAddr[16];	//!< source address
	u_int8_t dstAddr[16];	//!< destination address
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
		uint32_t setTrafficClass( uint32_t );
		//!Return the Flow Label field
		uint32_t flowLabel() const;
		//!Sets the Flow Label field
		uint32_t setFlowLabel( uint32_t );
		//!Return the Payload Length field
		uint16_t payloadLength() const;
		//!Sets the Payload Length field
		uint16_t setPayloadLength( uint16_t );
		//!Return the Next Header field
		uint8_t nextHeader() const;
		//!Sets the Next Header field
		uint16_t setNextHeader( uint8_t );
		//!Return the Hop Limit field
		uint8_t hopLimit() const;
		//!Sets the Hop Limit field
		uint8_t setHopLimit( uint8_t );
		//!Return the Source Address
		uint8_t srcAddr( 
}
