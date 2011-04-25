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

/** \file tcpStream.h
 * This is the declaration for the class TCPStream
 */

/** \class TCPStream 
 * This class is used in conjunction with StreamProcessor for handling TCPStreams
 *
 */



#ifndef TCPSTREAM_H 
#define TCPSTREAM_H

#include "../Packet/packet.h"
#include <vector>
#include <stdint.h>
#include "Stream.h"


class TCPSegment 
{
public:
	TCPSegment();
	virtual ~TCPSegment();
	void setData( const std::vector< uint8_t > &data );
	std::vector< uint8_t > data() const;
	void setSource( const uint32_t &source );
	uint32_t source() const;

private:
	std::vector< uint8_t > data_;
	uint8_t source_;
};

class TCPStream : public Stream
{
public:
	TCPStream();
	virtual ~TCPStream();
	std::string name() const;
	void processPacket( const Packet &p );
	void setServerIP( const uint32_t &ip );
	uint32_t serverIP() const;
	void setClientIP( const uint32_t &ip );
	uint32_t clientIP() const;
	void setServerPort( const uint16_t &port );
	uint16_t serverPort() const;
	void setClientPort( const uint16_t &port );
	uint16_t clientPort() const;
	void setCurrentServerSequenceNumber( const uint32_t &num );
	uint32_t currentServerSequenceNumber( ) const;
	void setCurrentClientSequenceNumber( const uint32_t &num );
	uint32_t currentClientSequenceNumber() const;
	void setCurrentServerAckNumber( const uint32_t &num );
	uint32_t currentServerAckNumber( ) const;
	void setCurrentClientAckNumber( const uint32_t &num );
	uint32_t currentClientAckNumber() const;
	void addTCPSegment( const TCPSegment& segment );
	int size() const;
	TCPSegment segment( const int &index ) const;

private:
	void initSyn( const Packet &p );
	void initSynAck( const Packet &p );
	uint32_t serverIp_;
	uint32_t clientIp_;
	uint16_t serverPort_;
	uint16_t clientPort_;
	uint32_t serverSequenceNumber_;
	uint32_t serverAcknowledgeNumber_;
	uint32_t clientSequenceNumber_;
	uint32_t clientAcknowledgeNumber_;
	uint32_t initialClientSequenceNumber_;
	uint32_t initialServerSequencenumber_;
	std::vector< TCPSegment > stream_;

};


#endif
