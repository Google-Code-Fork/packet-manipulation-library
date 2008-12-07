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

/** \file tcp.cpp
 * This is the definition for the class TCP 
 */


#include <stdexcept>
#include "tcp.h"
#include <iostream>

TCP::TCP()
{
  header_ = new struct my_tcp;
  setDataOffset( TCPStructSize );
//  std::cerr << "TCP SIZE: " << static_cast<uint16_t>(getDataOffset()) << std::endl;
}

TCP::TCP( const uint8_t *packet, int size )
{
  header_ = new struct my_tcp;
  int headerSize = TCPStructSize;
  if( size < headerSize )
    throw std::runtime_error( "Packet capture too small to make packet" );
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

uint16_t TCP::getSourcePort() const
{
  return ntohs( header_->sport );
}

void TCP::setSourcePort( uint16_t port )
{
  header_->sport = htons( port );
}

uint16_t TCP::getDestinationPort() const
{
  return ntohs( header_->dport );
}

void TCP::setDestinationPort( uint16_t port )
{
  header_->dport = htons( port );
}

uint32_t TCP::getSequenceNumber() const
{
  return ntohl( header_->sequenceNumber );
}

void TCP::setSequenceNumber( uint32_t num )
{
  header_->sequenceNumber = htonl( num );
}

uint32_t TCP::getAcknowledgementNumber() const
{
  return ntohl( header_->ackNumber );
}

void TCP::setAcknowledgementNumber( uint32_t ackNum )
{
  header_->ackNumber = htonl( ackNum );
}

uint8_t TCP::getDataOffset() const
{
  return OFFSET( header_ ) * 4;
}

void TCP::setDataOffset( uint8_t dataOffset )
{
  dataOffset /= 4;
  if( dataOffset &0xF0 )
    throw std::runtime_error( "Invalid DataOffset" );
  header_->dataOffset &= 0xF;
  header_->dataOffset |= dataOffset << 4;
}

bool TCP::getFlagsCWR() const
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

bool TCP::getFlagsECE() const
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

bool TCP::getFlagsURG() const
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

bool TCP::getFlagsACK() const
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

bool TCP::getFlagsPSH() const
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

bool TCP::getFlagsRST() const
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

bool TCP::getFlagsSYN() const
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

bool TCP::getFlagsFIN() const
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

uint16_t TCP::getWindow() const
{
  return ntohs( header_->window );
}

void TCP::setWindow( uint16_t windowSize )
{
  header_->window = htons( windowSize );
}

uint16_t TCP::getChecksum() const
{
  return ntohs( header_->checksum );
}

void TCP::setChecksum( uint16_t checksum )
{
  header_->checksum = htons( checksum );
}

uint16_t TCP::getUrgentPointer() const
{
  return ntohs( header_->urgentPointer );
}

void TCP::setUrgentPointer( uint16_t urgentPointer )
{
  header_->urgentPointer = htons( urgentPointer );
}

int TCP::getSize() const 
{
  return static_cast<int>( getDataOffset() );
}

PacketBuffer TCP::makePacket() const 
{
  std::vector< uint8_t > packet;
  int bytes = getSize();
  std::cerr << "SIZE: " << bytes << std::endl;
  uint8_t* ptr = (uint8_t*) header_;
  int sizeToCopy = bytes < TCPStructSize ? bytes : TCPStructSize;
  for( int i = 0; i < sizeToCopy; ++i )
  {
    packet.push_back( ptr[i] );
  }
  for( int i = 0; i < bytes-TCPStructSize; ++i )
    packet.push_back( 0 );
  return PacketBuffer( packet );
}
