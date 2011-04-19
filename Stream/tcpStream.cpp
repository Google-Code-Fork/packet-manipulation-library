/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011 Jeff Scaparra
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


#include "tcpStream.h"

TCPSegment::TCPSegment()
{

}

TCPSegment::~TCPSegment()
{

}

void TCPSegment::setData( const std::vector< uint8_t > &data )
{
	data_ = data;
}

std::vector< uint8_t > TCPSegment::data( ) const
{
	return data_;
}

void TCPSegment::setSource( const uint32_t &source )
{
	source_ = source;
}

uint32_t TCPSegment::source() const
{
	return source_;
}



TCPStream::TCPStream():serverIp_(0),clientIp_(0),serverPort_(0),clientPort_(0),serverSequenceNumber_(0),
	serverAcknowledgeNumber_(0),clientSequenceNumber_(0),clientAcknowledgeNumber_(0),initialClientSequenceNumber_( 0 ), 
	initialServerSequencenumber_(0)
{
}

TCPStream::~TCPStream()
{
}

void TCPStream::processPacket( const Packet &p )
{
	uint32_t senderip;
	std::vector< uint8_t > data;

	//Is TCP?
	if( p.transSize() > 0 && p.transIs<TCP>() )
	{
		TCP tcp = p.getTrans<TCP>();
		//check for syn packet
		if( tcp.SYN_Flag() )
		{
			//if syn initialize stream
			if( tcp.ACK_Flag() )
				initSynAck( p );
			else
				initSyn( p );
		}
		else
		{
			TCPSegment segment;
			if( p.appSize() > 0 && p.appIs< Raw >() )
			{
				segment.setData( p.getApp<Raw>( ).makePacket().vector() );
				if( p.inetSize() > 0 && p.inetIs< IPv4 >() )
				{
					segment.setSource( p.getInet<IPv4>().sourceAddress() );
				}
				if( segment.source() == serverIp_ )
				{
					serverSequenceNumber_ = tcp.sequenceNumber();
					serverAcknowledgeNumber_ = tcp.acknowledgementNumber();
				}
				else
				{
					clientSequenceNumber_ = tcp.sequenceNumber();
					clientAcknowledgeNumber_ = tcp.acknowledgementNumber();
				}

				stream_.push_back( segment );
			}
		}
	}
}

void TCPStream::initSyn( const Packet &p )
{
	if( p.inetSize() > 0 && p.inetIs< IPv4 >() )
	{
		serverIp_ = p.getInet<IPv4>().destinationAddress();
		clientIp_ = p.getInet<IPv4>().sourceAddress();
	}
	clientPort_ = p.getTrans<TCP>().sourcePort();
	serverPort_ = p.getTrans<TCP>().destinationPort();
	clientSequenceNumber_ = p.getTrans<TCP>().sequenceNumber();
	initialClientSequenceNumber_ = clientSequenceNumber_;
}

void TCPStream::initSynAck( const Packet &p )
{
	serverSequenceNumber_ = p.getTrans<TCP>().sequenceNumber();
	initialServerSequencenumber_ = serverSequenceNumber_;
	serverAcknowledgeNumber_ = p.getTrans<TCP>().acknowledgementNumber();
}

void TCPStream::setServerIP( const uint32_t &ip )
{
	serverIp_ = ip;
}

uint32_t TCPStream::serverIP( ) const
{
	return serverIp_;
}

void TCPStream::setClientIP( const uint32_t &ip )
{
	clientIp_ = ip;
}

uint32_t TCPStream::clientIP() const
{
	return clientIp_;
}

void TCPStream::setServerPort( const uint16_t &port )
{
	serverPort_ = port ;
}

uint16_t TCPStream::serverPort() const
{
	return serverPort_;
}

void TCPStream::setClientPort( const uint16_t &port )
{
	clientPort_ = port; 
}

uint16_t TCPStream::clientPort() const
{
	return clientPort_;
}

void TCPStream::setCurrentServerSequenceNumber( const uint32_t &num )
{
	serverSequenceNumber_ = num;
}

uint32_t TCPStream::currentServerSequenceNumber() const
{
	return serverSequenceNumber_;
}

void TCPStream::setCurrentServerAckNumber( const uint32_t &num )
{
	serverAcknowledgeNumber_ = num;
}

uint32_t TCPStream::currentServerAckNumber( ) const
{
	return serverAcknowledgeNumber_;
}

void TCPStream::setCurrentClientSequenceNumber( const uint32_t &num )
{
	clientSequenceNumber_ = num;
}

uint32_t TCPStream::currentClientSequenceNumber() const
{
	return clientSequenceNumber_;
}

void TCPStream::setCurrentClientAckNumber( const uint32_t &num )
{
	clientAcknowledgeNumber_ = num;
}

uint32_t TCPStream::currentClientAckNumber() const 
{
	return clientAcknowledgeNumber_;
}

void TCPStream::addTCPSegment( const TCPSegment &segment )
{
	stream_.push_back( segment );
}

int TCPStream::size() const
{
	int size = 0;
	for( int i = 0; i < stream_.size(); ++i )
	{
		size += stream_[i].data().size();
	}
	return size;
}

TCPSegment TCPStream::segment( const int &index ) const
{
	return stream_[index];
}
		
