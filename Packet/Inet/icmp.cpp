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


#include <iostream>
#include "icmp.h"
#include "../common/constants.h"
#include "packet.h"

ICMP::ICMP()
{
	header_ = new struct icmpHeader;
	request_ = NULL;
	orginal_ = NULL;
}

ICMP::ICMP( const uint8_t *packet, const int size)
{
	request_ = NULL;
	orginal_ = NULL;
	header_ = new icmpHeader;
	*header_ = *((icmpHeader*)packet);
	if( getType() == net::TimeOut)
	{
		//must keep the orginal packet info
		orginal_ = new Packet( );
		orginal_->startAtIPHeader( packet + 8, size - 8 );

		/***** DEBUG 
		if( orginal_->isIP() )
			std::cerr << "IP Packet" << std::endl;
		if( orginal_->isICMP() )
			std::cerr << "ICMP Packet :) " << std::endl;
		if( orginal_->isTCP() )
			std::cerr << "TCP PACKET :( " << std::endl;
			*/
	}

	if( getType() == net::EchoRequest || getType() == net::EchoReply )
	{
		request_ = new icmpRequest;
		*request_ = *((icmpRequest*)(packet + sizeof( icmpHeader )));
	}

}

ICMP::~ICMP()
{
	if( header_ )
		delete header_;
	if( request_ )
		delete request_;
	if( orginal_ )
		delete orginal_;
}

ICMP::ICMP( const ICMP &n )
{
	request_ = NULL;
	orginal_ = NULL;
	header_ = new icmpHeader;
	*header_ = *(n.header_);

	if( n.request_ )
	{
		request_ = new icmpRequest;
		*request_ = *(n.request_);
	}
	
	if( n.orginal_ )
	{
		orginal_ = new Packet;
		*orginal_ = *(n.orginal_);
	}
}

ICMP& ICMP::operator= ( const ICMP &n )
{
	*header_ = *( n.header_ );
	if( n.request_ )
	{
		if( request_ == NULL )
			request_ = new icmpRequest;
		*request_ = *(n.request_);
	}
	else
	{
		if( request_ )
			delete request_;
		request_ = NULL;
	}
	
	if( n.orginal_ )
	{
		if( orginal_ == NULL )
			orginal_ = new Packet;
		*orginal_ = *(n.orginal_);
	}
	else
	{
		if( orginal_ )
			delete orginal_;
		orginal_ = NULL;
	}
}

uint8_t ICMP::getType()
{
	return header_->type;
}

void ICMP::setType( uint8_t type )
{
	header_->type = type;
	if( type == 8 || type == 0 )
	{
		request_ = new icmpRequest;
		request_->identifier = 0;
		request_->sequence = 0;
	}
	else
	{
		if( request_ )
			delete request_;
	}
}

uint8_t ICMP::getCode()
{
	return header_->code;
}

void ICMP::setCode( uint8_t code )
{
	header_->code = code;
}

uint16_t ICMP::getChecksum()
{
	return header_->checkSum;
}

void ICMP::setChecksum( uint16_t checksum )
{
	header_->checkSum = checksum;
}

void ICMP::generateChecksum()
{
	int size = 0;
	if( header_ == NULL )
	{
		throw std::runtime_error( "ICMP header has NULL value" );
	}
	size += sizeof(icmpHeader); 

	if( request_ != NULL )
	{
		size += sizeof( icmpRequest );
	}
	header_->checkSum = 0;

	uint8_t *pointer;
	uint16_t buffer [ (size%2) == 0 ? (size/2) : (size/2)+1 ];
	*(icmpHeader*)buffer = *header_;
	pointer = (uint8_t*)buffer + sizeof( icmpHeader );
	*(icmpRequest*)pointer = *request_;
	header_->checkSum = icmpChecksum( buffer, size );


}


uint16_t icmpChecksum (uint16_t * buffer, int numOfBytes)
{
	uint64_t cksum = 0;
	/* sum all the words together, adding the final byte if size is odd */
	while ( numOfBytes > 1)
	{
		cksum += *buffer++;
		numOfBytes -= sizeof (uint16_t);
	}
	if (numOfBytes)
		cksum += *(uint8_t *) buffer;
	/* do a little shuffling */
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	/* return the bitwise complement of the resulting mishmash */
	return (uint16_t) (~cksum);
}

int ICMP::getHeaderLength()
{
	int size = 0;
	if( header_ )
		size += sizeof( icmpHeader );
	if( request_ )
	{
		size += sizeof( icmpRequest );
	}
	return size;
}



uint16_t ICMP::getIdentifier()
{
	if( request_ == NULL )
		throw std::runtime_error( "ICMP WRONG TYPE" );
	return request_->identifier;
}

void ICMP::setIdentifier( uint16_t identifier )
{
	if( !request_ )
		throw std::runtime_error( "ICMP WRONG TYPE" );
	request_->identifier = identifier;
}

uint16_t ICMP::getSequenceNum()
{
	if( !request_ )
		throw std::runtime_error( "ICMP WRONG TYPE" );
	return request_->sequence;
}

void ICMP::setSequenceNum( uint16_t sequence )
{
	if( !request_ )
		throw std::runtime_error( "ICMP WRONG TYPE" );
	request_->sequence = sequence;
}

Packet ICMP::getOrginalPacket()
{
	if( header_->type != 11 )
		throw std::runtime_error( "ICMP WRONG TYPE - Needs 11" );
	PacketBuilder pb;
	return pb.buildPacket<Ethernet>( orginal_ );
}

PacketBuffer ICMP::makePacket() const
{

}
