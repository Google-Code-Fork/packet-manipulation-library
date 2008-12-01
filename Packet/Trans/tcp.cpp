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
#include "tcp.h"

TCP::TCP()
{
	header_ = new struct my_tcp;
}

TCP::TCP( const uint8_t *packet )
{
	header_ = new struct my_tcp;
	*header_ = *((struct my_tcp*)packet);
}

TCP::TCP( const TCP &n )
{
	header_ = new struct my_tcp;
	*header_ = *(n.header_);
}

TCP& TCP::operator =( const TCP &n )
{
	*header_ = *(n.header_);
}

TCP::~TCP()
{
	delete header_;
}

uint16_t TCP::getSourcePort()
{
	return ntohs( header_->sport );
}

void TCP::setSourcePort( uint16_t port )
{
	header_->sport = htons( port );
}

uint16_t TCP::getDestinationPort()
{
	return ntohs( header_->dport );
}

void TCP::setDestinationPort( uint16_t port )
{
	header_->dport = htons( port );
}

uint32_t TCP::getSequenceNumber()
{
	return ntohl( header_->sequenceNumber );
}

void TCP::setSequenceNumber( uint32_t num )
{
	header_->sequenceNumber = htonl( num );
}

uint32_t TCP::getAcknowledgementNumber()
{
	return ntohl( header_->ackNumber );
}

void TCP::setAcknowledgementNumber( uint32_t ackNum )
{
	header_->ackNumber = htonl( ackNum );
}

uint8_t TCP::getDataOffset()
{
	return OFFSET( header_ ) * 4;
}

void TCP::setDataOffset( uint8_t dataOffset )
{
	if( dataOffset &0xF0 )
		throw std::runtime_error( "Invalid DataOffset" );
	header_->dataOffset &= 0xF;
	header_->dataOffset |= dataOffset << 4;
}

bool TCP::getFlagsCWR()
{
	return (( 0 < ( header_->flags & TCP_CWR ) ) );
}

void TCP::setFlagsCWR()
{
	setFlagsCWR( true );
}

void TCP::setFlagsCWR( bool set )
{
	set ? header_->flags |= TCP_CWR : header_->flags & (TCP_CWR ^ 0xFF);
}

bool TCP::getFlagsECE()
{
	return ( 0 < ( header_->flags & TCP_ECE ) );
}

void TCP::setFlagsECE()
{
	setFlagsECE( true );
}

void TCP::setFlagsECE( bool set )
{
	set ? header_->flags |= TCP_ECE : header_->flags & (TCP_ECE ^ 0xFF);
}

bool TCP::getFlagsURG()
{
	return ( 0 < ( header_->flags & TCP_URG ) );
}

void TCP::setFlagsURG()
{
	setFlagsURG( true );
}

void TCP::setFlagsURG( bool set )
{
	set ? header_->flags |= TCP_URG : header_->flags & (TCP_URG ^ 0xFF);
}

bool TCP::getFlagsACK()
{
	return ( 0 < ( header_->flags & TCP_ACK ) );
}

void TCP::setFlagsACK()
{
	setFlagsACK( true );
}

void TCP::setFlagsACK( bool set )
{
	set ? header_->flags |= TCP_ACK : header_->flags & (TCP_ACK ^ 0xFF);
}

bool TCP::getFlagsPSH()
{
	return ( 0 < ( header_->flags & TCP_PSH ) );
}

void TCP::setFlagsPSH( )
{
	setFlagsPSH( true );
}

void TCP::setFlagsPSH( bool set )
{
	set ? header_->flags |= TCP_ACK : header_->flags & (TCP_ACK ^ 0xFF);
}

bool TCP::getFlagsRST()
{
	return ( 0 < ( header_->flags & TCP_RST ) );
}

void TCP::setFlagsRST( )
{
	setFlagsRST( true );
}

void TCP::setFlagsRST( bool set )
{
	set ? header_->flags |= TCP_RST : header_->flags & (TCP_RST ^ 0xFF);
}

bool TCP::getFlagsSYN()
{
	return ( 0 < ( header_->flags & TCP_SYN ) );
}

void TCP::setFlagsSYN( )
{
	setFlagsSYN( true );
}

void TCP::setFlagsSYN( bool set )
{
	set ? header_->flags |= TCP_SYN : header_->flags & (TCP_SYN ^ 0xFF);
}

bool TCP::getFlagsFIN()
{
	return ( 0 < ( header_->flags & TCP_FIN ) );
}

void TCP::setFlagsFIN( )
{
	setFlagsFIN( true );
}

void TCP::setFlagsFIN( bool set )
{
	set ? header_->flags |= TCP_SYN : header_->flags & (TCP_SYN ^ 0xFF);
}

uint16_t TCP::getWindow()
{
	return ntohs( header_->window );
}

void TCP::setWindow( uint16_t windowSize )
{
	header_->window = htons( windowSize );
}

uint16_t TCP::getChecksum()
{
	return ntohs( header_->checksum );
}

void TCP::setChecksum( uint16_t checksum )
{
	header_->checksum = htons( checksum );
}

uint16_t TCP::getUrgentPointer()
{
	return ntohs( header_->urgentPointer );
}

void TCP::setUrgentPointer( uint16_t urgentPointer )
{
	header_->urgentPointer = htons( urgentPointer );
}

int TCP::getSize()
{
  return static_cast<int>( getDataOffset() );
}

std::vector< uint8_t > TCP::makePacket()
{
  std::vector< uint8_t > packet;
  int bytes = getSize();
  uint8_t* ptr = (uint8_t*) header_;
  int sizeToCopy = bytes < TCPStructSize ? bytes : TCPStructSize;
  for( int i = 0; i < sizeToCopy; ++i )
  {
    packet.push_back( ptr[i] );
  }
  for( int i = 0; i < bytes-TCPStructSize; ++i )
    packet.push_back( 0 );
  return packet;
}
