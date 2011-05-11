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

/** \file udp.cpp
 * This is the definition for the class UDP
 */


#include "udp.h"
#include <stdexcept>
#include <iostream>
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
  return *this;
}

UDP::~UDP()
{
	delete header_;
}

uint16_t UDP::sourcePort() const
{
	return ntohs( header_->sport );
}

void UDP::setSourcePort( uint16_t port )
{
	header_->sport = htons( port );
}

uint16_t UDP::destinationPort() const
{
	return ntohs( header_->dport );
}

void UDP::setDestinationPort( uint16_t port )
{
	header_->dport = htons( port );
}

uint16_t UDP::checksum() const
{
	return ntohs( header_->checksum );
}

void UDP::setChecksum( uint16_t checksum )
{
	header_->checksum = htons( checksum );
}

uint16_t UDP::length() const
{
	return ntohs( header_->length );
}

void UDP::setLength( uint16_t length )
{
	header_->length = htons( length );
}

int UDP::size() const
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

void UDP::calculateChecksum( const uint32_t &sourceAddress, const uint32_t
		&destinationAddress, const std::vector< uint8_t > &data )
{
	setChecksum( 0x0000 );
	uint32_t source = htonl( sourceAddress );
	uint32_t destination = htonl( destinationAddress );
	uint16_t protocol = htons(17);
	uint16_t datalength = htons( sizeof(*header_) + data.size());

	uint32_t sum = 0;

	sum += (source >> 16) + (source & 0xFFFF);
	sum += (destination >> 16) + (destination & 0xFFFF);
	sum += protocol;
	sum += datalength;

	std::vector< uint8_t > header = makePacket().vector();
  for( uint32_t i = 0; i < header.size(); i +=2 )
	{
		uint16_t tmp = header[i];
		tmp <<= 8;
		tmp |= header[i+1];
		sum += htons(tmp);
	}

	std::vector< uint8_t > tmpData = data;
	if( data.size() % 2 )
		tmpData.push_back( 0x00 );

  for( uint32_t i = 0; i < tmpData.size(); i += 2 )
	{
		uint16_t tmp = tmpData[i];
		tmp <<= 8;
		tmp |= tmpData[i+1];
		sum += htons(tmp);
	}

	while( sum >> 16 )
	{
		sum = (sum & 0xFFFF) + (sum >> 16);
	}

	header_->checksum = ~sum;
}
