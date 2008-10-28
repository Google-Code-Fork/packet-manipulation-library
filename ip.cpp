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

#include <stdexcept>
#include "ip.h"
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>

IP::IP( )
{
	header_ = new struct my_ip;
}

IP::IP( const uint8_t *packet )
{
	header_ = new struct my_ip;
	*header_ = *((struct my_ip*)packet);
}

IP::~IP()
{
	delete header_;
}

IP::IP( const IP &n )
{
	header_ = new struct my_ip;
	*header_ = *(n.header_);
}

IP& IP::operator =( const IP &n )
{
	*header_ = *(n.header_);
}

uint8_t IP::getVersion()
{
	uint8_t version = header_->ip_vhl;
	return ((version & 0xf0) >> 4); 
}

void IP::setVersion( uint8_t version )
{
	if( 0 < 0xF0 & version )
		throw std::runtime_error( "Invaild IP Version" );
	header_->ip_vhl &= 0x0F; //Save the Header Length bits
	header_->ip_vhl |= version << 4;
}

uint8_t IP::getHeaderLength()
{
	uint8_t headerLength = header_->ip_vhl;
	return ((headerLength & 0x0F ) * 4);
}

void IP::setHeaderLength( uint8_t headerLength )
{
	headerLength /= 4;
	header_->ip_vhl &= 0xF0; //Save off the version bits
	header_->ip_vhl |= headerLength & 0xF;
}

uint16_t IP::getTotalLength()
{
	return ntohs( header_->ip_len);
}

void IP::setTotalLength( uint16_t length )
{
	header_->ip_len = length;
}

uint16_t IP::getIdentifaction()
{
	return ntohs( header_->ip_id);
}

void IP::setIdentifaction( uint16_t id )
{
	header_->ip_id = htons( id );
}

bool IP::getFlagsNoFragment()
{
	return (  0 < (header_->ip_off & IP_DF) );
}

void IP::setFlagsNoFragment()
{
	setFlagsNoFragment( true );
}

void IP::setFlagsNoFragment( bool set )
{
	set ? header_->ip_off |= IP_DF : header_->ip_off &= 0x3FFF;
}

bool IP::getFlagsMoreFragments()
{
	return (  0 < (header_->ip_off & IP_MF) );
}

void IP::setFlagsMoreFragments( bool set )
{
	set ? header_->ip_off |= IP_MF : header_->ip_off &= 0x5FFF;
}

void IP::setFlagsMoreFragments( )
{
	setFlagsMoreFragments( true );
}

uint16_t IP::getFragmentOffset()
{
	return header_->ip_off & IP_OFFMASK;
}

void IP::setFragmentOffset( uint16_t fragmentOffset )
{
	if( fragmentOffset & 0x6000 )
		throw std::runtime_error( "Invalid Fragment Offset" );
	header_->ip_off |= fragmentOffset & IP_OFFMASK;
}

uint8_t IP::getTTL()
{
	return header_->ip_ttl;
}

void IP::setTTL( uint8_t ttl )
{
	header_->ip_ttl = ttl;
}

uint8_t IP::getProtocol()
{
	return header_->ip_p;
}

void IP::setProtocol( uint8_t protocol )
{
	header_->ip_p = protocol;
}

uint16_t IP::getChecksum()
{
	return ntohs( header_->ip_sum );
}

void IP::setChecksum( uint16_t checksum )
{
	header_->ip_sum = htons( checksum );
}

uint32_t IP::getSourceAddress()
{
	return header_->ip_src.s_addr;
}

void IP::setSourceAddress( uint32_t ip )
{
	header_->ip_src.s_addr = ip;
}

uint32_t IP::getDestinationAddress()
{
	return header_->ip_dst.s_addr;
}

void IP::setDestinationAddress( uint32_t ip )
{
	 header_->ip_dst.s_addr = ip;
}
