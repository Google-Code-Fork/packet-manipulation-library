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


#include "udp.h"
#include <stdexcept>

UDP::UDP()
{
	header_ = new struct my_udp;
}

UDP::UDP( const uint8_t *packet, int size )
{
	header_ = new struct my_udp;
	int headerSize = sizeof( header_ );
	if( size < headerSize )
	  throw std::runtime_error( "Packet capture too small" );
	*header_ = *((struct my_udp*)packet);
}

UDP::UDP( const UDP &n )
{
	header_ = new struct my_udp;
	*header_ = *(n.header_);
}

UDP& UDP::operator =( const UDP &n )
{
	*header_ = *(n.header_);
}

UDP::~UDP()
{
	delete header_;
}

uint16_t UDP::getSourcePort() const
{
	return ntohs( header_->sport );
}

void UDP::setSourcePort( uint16_t port )
{
	header_->sport = htons( port );
}

uint16_t UDP::getDestinationPort() const
{
	return ntohs( header_->dport );
}

void UDP::setDestinationPort( uint16_t port )
{
	header_->dport = htons( port );
}

uint16_t UDP::getChecksum() const
{
	return ntohs( header_->checksum );
}

void UDP::setChecksum( uint16_t checksum )
{
	header_->checksum = htons( checksum );
}

uint16_t UDP::getLength() const
{
	return ntohs( header_->length );
}

void UDP::setLength( uint16_t length )
{
	header_->length = htons( length );
}

int UDP::getSize() const
{
  return UDPSize;
}

PacketBuffer UDP::makePacket() const
{
  std::vector< uint8_t > packet;
  uint8_t* ptr = (uint8_t*) header_;
  for( int i = 0; i < UDPSize; ++i )
    packet.push_back( ptr[i] );
  return PacketBuffer( packet );
}
