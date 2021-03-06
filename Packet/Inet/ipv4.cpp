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

/** \file ipv4.cpp
 * This is the definition for the class IPv4
 */

#include <stdexcept>
#include "ipv4.h"
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>
#include <sstream>

IPv4::IPv4( )
{
	header_ = new struct IPv4Header;
	setHeaderLength( 20 );
}

IPv4::IPv4( const uint8_t *packet, int size )
{
	header_ = new struct IPv4Header;
	int headerSize = 20;
	if( size < headerSize )
	  throw std::runtime_error( "packet capture too small to make packet" );
	*header_ = *((struct IPv4Header*)packet);
}

IPv4::~IPv4()
{
	delete header_;
}

IPv4::IPv4( const IPv4 &n )
{
	header_ = new struct IPv4Header;
	*header_ = *(n.header_);
}

IPv4& IPv4::operator =( const IPv4 &n )
{
	*header_ = *(n.header_);
  return *this;
}

uint8_t IPv4::version() const
{
	uint8_t version = header_->ip_vhl;
	return ((version & 0xf0) >> 4); 
}

void IPv4::setVersion( uint8_t version )
{
	//if the version is too large to fit in the feild 
	if( 0 < (0xF0 & version) )
		throw std::runtime_error( "Invaild IPv4 Version" );
	header_->ip_vhl &= 0x0F; //Save the Header Length bits
	header_->ip_vhl |= version << 4;
}

uint8_t IPv4::headerLength() const
{
	uint8_t headerLength = header_->ip_vhl;
  return ((headerLength & 0x0FU ) * 4U);
}

void IPv4::setHeaderLength( uint8_t headerLength )
{
	headerLength /= 4;
	header_->ip_vhl &= 0xF0; //Save off the version bits
	header_->ip_vhl |= headerLength & 0xF;
}

uint16_t IPv4::totalLength() const
{
	return ntohs( header_->ip_len);
}

void IPv4::setTotalLength( uint16_t length )
{
	header_->ip_len = htons(length);
}

uint16_t IPv4::identification() const
{
	return ntohs( header_->ip_id);
}

void IPv4::setIdentification( uint16_t id )
{
	header_->ip_id = htons( id );
}

bool IPv4::dontFragment() const
{
	return (  0 < (ntohs(header_->ip_off) & IP_DF) );
}

void IPv4::setDontFragment()
{
	setDontFragment( true );
}

void IPv4::setDontFragment( bool set )
{
	set ? header_->ip_off |= htons(IP_DF) : header_->ip_off &= htons(0x3FFF);
}

bool IPv4::moreFragments() const
{
	return (  0 < (ntohs(header_->ip_off) & IP_MF) );
}

void IPv4::setMoreFragments( bool set )
{
	set ? header_->ip_off |= htons(IP_MF) : header_->ip_off &= htons(0x5FFF);
}

void IPv4::setMoreFragments( )
{
	setMoreFragments( true );
}

uint16_t IPv4::fragmentOffset() const
{
	return ntohs(header_->ip_off) & IP_OFFMASK;
}

void IPv4::setFragmentOffset( uint16_t fragmentOffset )
{
	if( fragmentOffset & 0x6000 ) //too large to fit
		throw std::runtime_error( "Invalid Fragment Offset" );
	header_->ip_off |= htons(fragmentOffset & IP_OFFMASK);
}

uint8_t IPv4::ttl() const
{
	return header_->ip_ttl;
}

void IPv4::setTtl( uint8_t ttl )
{
	header_->ip_ttl = ttl;
}

uint8_t IPv4::protocol() const
{
	return header_->ip_p;
}

void IPv4::setProtocol( uint8_t protocol )
{
	header_->ip_p = protocol;
}

uint16_t IPv4::checksum() const
{
	return ntohs( header_->ip_sum );
}

void IPv4::setChecksum( uint16_t checksum )
{
	header_->ip_sum = htons( checksum );
}

IPv4Address IPv4::sourceAddress() const
{
  return IPv4Address( ntohl(header_->ip_src.s_addr) );
}

void IPv4::setSourceAddress( const IPv4Address &ip )
{
  header_->ip_src.s_addr = htonl(ip.inAddr());
}

IPv4Address IPv4::destinationAddress() const
{
  return IPv4Address( ntohl(header_->ip_dst.s_addr) );
}

void IPv4::setDestinationAddress( const IPv4Address &ip )
{
   header_->ip_dst.s_addr = htonl(ip.inAddr());
}

PacketBuffer IPv4::makePacket( ) const
{
  std::vector< uint8_t > packet;
  int bytes = headerLength();
  uint8_t* ptr = (uint8_t*)( header_ );
  for( int i = 0; i < bytes; ++i )
  {
    packet.push_back( ptr[i] );
  }
  return PacketBuffer( packet );
}

int IPv4::size() const
{
  return sizeof( *header_ );
}

void IPv4::calculateChecksum() 
{
	setChecksum(0);
	uint32_t sum = 0;
	std::vector< uint8_t > bytes = makePacket().vector();

  for( uint32_t i = 0; i < bytes.size(); i +=2 )
	{
		uint16_t tmp = bytes[i];
		tmp <<= 8;
		tmp |= bytes[i+1];
		sum += tmp;
	}

	while( sum >> 16 )
	{
		sum = (sum & 0xFFFF) + (sum >> 16);
	}

	setChecksum(static_cast<uint16_t>( ~sum ) );
}
