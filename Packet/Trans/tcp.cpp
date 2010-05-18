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

	int optionSize = header_->dataOffset - 5; //5 is the minimum size for tcp with NO options
	optionSize *= 4; //in bytes
	optionSize = optionSize + TCPStructSize - size < optionSize ? 
																		size - TCPStructSize : optionSize;

	for( int i = 0; i < optionSize;  )
	{
		switch( packet[ i + TCPStructSize ] )
		{
			case 0: //END OF LIST
				{
					SmartPtr< TCPOption > option0( new EOLOption() );
					options_.push_back( option0 );
					i = i + option0->length();
				}
				break;
			case 1: //NO-OP
				{
					SmartPtr< TCPOption > option1( new NOOPOption() );
					options_.push_back( option1 );
					i = i + option1->length();
				}
				break;
			case 2: //MSS
				{
					SmartPtr< TCPOption > option2( new MSSOption( packet+(i+TCPStructSize), optionSize - i) );
					options_.push_back( option2 );
					i = i + option2->length();
				}
				break;
			case 3: //Window Scale
				{
					SmartPtr< TCPOption > option3( new WSOption( packet+(i + TCPStructSize),
								optionSize - i ) );
					options_.push_back( option3 );
					i = i + option3->length();
				}
				break;
			case 4: //SACK PREMITTED
				{
					SmartPtr< TCPOption > option4( new SACKPremittedOption() ); 
					options_.push_back( option4 );
					i = i + option4->length();
				}
				break;
			case 5: //SACK 
				{
					SmartPtr< TCPOption > option5( new SACKOption( packet+(i+TCPStructSize), optionSize - i) ); 
					options_.push_back( option5 );
					i = i + option5->length();
				}
				break;
			case 8: //Time Stamp Option
				{
					SmartPtr< TCPOption > option8( new TimeStampOption( packet+(i+TCPStructSize), optionSize - i) ); 
					options_.push_back( option8 );
					i = i + option8->length();
				}
				break;
		//	default:
		};


	}

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

uint16_t TCP::sourcePort() const
{
  return ntohs( header_->sport );
}

void TCP::setSourcePort( uint16_t port )
{
  header_->sport = htons( port );
}

uint16_t TCP::destinationPort() const
{
  return ntohs( header_->dport );
}

void TCP::setDestinationPort( uint16_t port )
{
  header_->dport = htons( port );
}

uint32_t TCP::sequenceNumber() const
{
  return ntohl( header_->sequenceNumber );
}

void TCP::setSequenceNumber( uint32_t num )
{
  header_->sequenceNumber = htonl( num );
}

uint32_t TCP::acknowledgementNumber() const
{
  return ntohl( header_->ackNumber );
}

void TCP::setAcknowledgementNumber( uint32_t ackNum )
{
  header_->ackNumber = htonl( ackNum );
}

uint8_t TCP::dataOffset() const
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

uint8_t TCP::x2() const
{
	return X2( header_ );
}

void TCP::setX2( uint8_t x2 )
{
	header_->dataOffset &= 0x0F;
	header_->dataOffset |= (x2 & 0x0F);
}

bool TCP::CWR_Flag() const
{
  return (( 0 < ( header_->flags & TCP_CWR ) ) );
}

void TCP::setCWR_Flag()
{
  setCWR_Flag( true );
}

void TCP::setCWR_Flag( bool set )
{
  set ? header_->flags |= TCP_CWR : header_->flags & (TCP_CWR ^ 0xFF);
}

bool TCP::ECE_Flag() const
{
  return ( 0 < ( header_->flags & TCP_ECE ) );
}

void TCP::setECE_Flag()
{
  setECE_Flag( true );
}

void TCP::setECE_Flag( bool set )
{
  set ? header_->flags |= TCP_ECE : header_->flags & (TCP_ECE ^ 0xFF);
}

bool TCP::URG_Flag() const
{
  return ( 0 < ( header_->flags & TCP_URG ) );
}

void TCP::setURG_Flag()
{
  setURG_Flag( true );
}

void TCP::setURG_Flag( bool set )
{
  set ? header_->flags |= TCP_URG : header_->flags & (TCP_URG ^ 0xFF);
}

bool TCP::ACK_Flag() const
{
  return ( 0 < ( header_->flags & TCP_ACK ) );
}

void TCP::setACK_Flag()
{
  setACK_Flag( true );
}

void TCP::setACK_Flag( bool set )
{
  set ? header_->flags |= TCP_ACK : header_->flags & (TCP_ACK ^ 0xFF);
}

bool TCP::PSH_Flag() const
{
  return ( 0 < ( header_->flags & TCP_PSH ) );
}

void TCP::setPSH_Flag( )
{
  setPSH_Flag( true );
}

void TCP::setPSH_Flag( bool set )
{
  set ? header_->flags |= TCP_ACK : header_->flags & (TCP_ACK ^ 0xFF);
}

bool TCP::RST_Flag() const
{
  return ( 0 < ( header_->flags & TCP_RST ) );
}

void TCP::setRST_Flag( )
{
  setRST_Flag( true );
}

void TCP::setRST_Flag( bool set )
{
  set ? header_->flags |= TCP_RST : header_->flags & (TCP_RST ^ 0xFF);
}

bool TCP::SYN_Flag() const
{
  return ( 0 < ( header_->flags & TCP_SYN ) );
}

void TCP::setSYN_Flag( )
{
  setSYN_Flag( true );
}

void TCP::setSYN_Flag( bool set )
{
  set ? header_->flags |= TCP_SYN : header_->flags & (TCP_SYN ^ 0xFF);
}

bool TCP::FIN_Flag() const
{
  return ( 0 < ( header_->flags & TCP_FIN ) );
}

void TCP::setFIN_Flag( )
{
  setFIN_Flag( true );
}

void TCP::setFIN_Flag( bool set )
{
  set ? header_->flags |= TCP_SYN : header_->flags & (TCP_SYN ^ 0xFF);
}

uint16_t TCP::windowSize() const
{
  return ntohs( header_->window );
}

void TCP::setWindowSize( uint16_t windowSize )
{
  header_->window = htons( windowSize );
}

uint16_t TCP::checksum() const
{
  return ntohs( header_->checksum );
}

void TCP::setChecksum( uint16_t checksum )
{
  header_->checksum = htons( checksum );
}

uint16_t TCP::urgentPointer() const
{
  return ntohs( header_->urgentPointer );
}

void TCP::setUrgentPointer( uint16_t urgentPointer )
{
  header_->urgentPointer = htons( urgentPointer );
}

int TCP::size() const 
{
  return static_cast<int>( dataOffset() );
}

PacketBuffer TCP::makePacket() const 
{
  std::vector< uint8_t > packet;
  int bytes = size();
  std::cerr << "SIZE: " << bytes << std::endl;
  uint8_t* ptr = (uint8_t*) header_;
  int sizeToCopy = bytes < TCPStructSize ? bytes : TCPStructSize;
  for( int i = 0; i < sizeToCopy; ++i )
  {
    packet.push_back( ptr[i] );
  }
  for( int i = 0; i < bytes-TCPStructSize; ++i )
    packet.push_back( 0 );
	std::vector< SmartPtr< TCPOption > >::const_iterator itr;
	for( itr = options_.begin(); itr != options_.end(); ++itr )
	{
		std::vector< uint8_t > bytes = (*itr)->packetData();

	}
  return PacketBuffer( packet );
}
