/*
 * \file ipv6.cpp
 * This is the definition for the class IPv6
*/

#include <stdexcept>
#include "ipv6.h"
#include "ipv6Address.h"
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>

IPv6::IPv6()
{
	header_ = new struct IPv6Header;
}

IPv6::IPv6( const uint8_t *packet, const int &size )
{
	header_ = new struct IPv6Header;
  int headerSize = sizeof( *header_ );
  if ( size < headerSize + (IPv6Address::IPv6AddressSize * 2) )
		throw std::runtime_error( "packet capture too small to make packet" );
  *header_ = *((struct IPv6Header*)packet);
  IPv6Address src( (packet+headerSize) );
  srcAddress_ = src;
  IPv6Address dst( (packet+headerSize+IPv6Address::IPv6AddressSize) );
  dstAddress_ = dst;
}

IPv6::~IPv6()
{
	delete header_;
}

IPv6::IPv6( const IPv6 &n )
{
	header_ = new struct IPv6Header;
	*header_ = *(n.header_);
}

IPv6& IPv6::operator = ( const IPv6 &n )
{
	*header_ = *(n.header_);
  return *this;
}

uint8_t IPv6::version() const
{
  uint32_t version = ntohl(header_->ip_vtf);
  return static_cast<uint8_t>((version & 0xF0000000) >> 28);
}

void IPv6::setVersion( const uint8_t &version )
{
  uint32_t ver = static_cast<uint32_t>(version) << 28;
  header_->ip_vtf &= 0x0FFFFFFF;
  header_->ip_vtf |= ver;
}

uint32_t IPv6::trafficClass() const
{
	uint32_t trafficClass = header_->ip_vtf;
	return ((trafficClass & 0x0FF00000 ) >> 20);
}

void IPv6::setTrafficClass( const uint32_t &tClass )
{
	//if traffic class too large to fit in the field
	if( 0 < (0xFFFFFF00 & tClass) )
		throw std::runtime_error( "Invalid IPv6 Traffic Class size" );
	header_->ip_vtf &= 0xF00FFFFF; //Save Version and Flow Label fields
	header_->ip_vtf |= tClass << 20;
}

uint32_t IPv6::flowLabel() const
{
	uint32_t flowLabel = header_->ip_vtf;
	return (flowLabel & 0x000FFFFF);
}

void IPv6::setFlowLabel( const uint32_t &fLabel )
{
	//if flow label too large to fit in the field
	if( 0 < (0xFFF00000 & fLabel) )
		throw std::runtime_error( "Invalid IPv6 Flow Label field size" );
	header_->ip_vtf &= 0xFFF00000;
	header_->ip_vtf |= fLabel;
}

uint16_t IPv6::payloadLength() const
{
	return ntohs( header_->ip_len );
}

void IPv6::setPayloadLength( const uint16_t &length )
{
	header_->ip_len = htons( length );
}

uint8_t IPv6::nextHeader() const
{
  return  header_->ip_nh;
}

void IPv6::setNextHeader( const uint8_t &nextHeader )
{
	header_->ip_nh = htons( nextHeader );
}

uint8_t IPv6::hopLimit() const
{
  return header_->ip_hl;
}

void IPv6::setHopLimit( const uint8_t &hopLimit )
{
  header_->ip_hl = hopLimit;
}

//**********************************

IPv6Address IPv6::sourceAddress() const
{
  return srcAddress_;
}

void IPv6::setSourceAddress( const IPv6Address &v6 )
{
  srcAddress_ = v6;
}

IPv6Address IPv6::destinationAddress() const
{
  return dstAddress_;
}

void IPv6::setDestinationAddress( const IPv6Address &v6 )
{
  dstAddress_ = v6;
}




