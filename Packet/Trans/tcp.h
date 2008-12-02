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


#ifndef TCP_H 
#define TCP_H

#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include "transData.h"

struct my_tcp {
	u_int16_t sport; //source port
	u_int16_t dport; //destination port
	u_int32_t sequenceNumber; 
	u_int32_t ackNumber;
	u_int8_t dataOffset;
	#define OFFSET(tcp)  (((tcp)->dataOffset & 0xF0) >> 4)
	u_int8_t flags;
	#define TCP_CWR 0x80
	#define TCP_ECE 0x40
	#define TCP_URG 0x20
	#define TCP_ACK 0x10
	#define TCP_PSH 0x08
	#define TCP_RST 0x04
	#define TCP_SYN 0x02
	#define TCP_FIN 0x01
	u_int16_t window;
	u_int16_t checksum;
	u_int16_t urgentPointer;
};


class TCP : public TransData
{
  static const uint8_t TCPStructSize=20; //size of the above struct
	public:
		TCP();
		TCP( const uint8_t *packet, int size );
		TCP( const TCP &n );
		TCP& operator =( const TCP &n );

		~TCP();

		uint16_t getSourcePort() const;
		void setSourcePort( uint16_t );
		uint16_t getDestinationPort() const;
		void setDestinationPort( uint16_t );
		uint32_t getSequenceNumber() const;
		void setSequenceNumber( uint32_t );
		uint32_t getAcknowledgementNumber() const;
		void setAcknowledgementNumber( uint32_t );
		uint8_t getDataOffset() const;
		void setDataOffset( uint8_t );
		bool getFlagsCWR() const;
		void setFlagsCWR( bool );
		void setFlagsCWR( ); // ==setFlagsCWR( true );
		bool getFlagsECE() const;
		void setFlagsECE( bool );
		void setFlagsECE( ); // == setFlagsECE( true );
		bool getFlagsURG() const;
		void setFlagsURG( bool );
		void setFlagsURG( ); // == setFlagsURG( true );
		bool getFlagsACK() const;
		void setFlagsACK( bool );
		void setFlagsACK( ); // == setFlagsACK( true );
		bool getFlagsPSH() const;
		void setFlagsPSH( bool );
		void setFlagsPSH( ); // == setFlagsPSH( true );
		bool getFlagsRST() const;
		void setFlagsRST( bool );
		void setFlagsRST( ); // == setFlagsRST( true );
		bool getFlagsSYN() const;
		void setFlagsSYN( bool );
		void setFlagsSYN( ); // == setFlagsSYN( true );
		bool getFlagsFIN() const;
		void setFlagsFIN( bool );
		void setFlagsFIN( ); // == setFlagsFIN( true );
		uint16_t getWindow() const;
		void setWindow( uint16_t ); 
		uint16_t getChecksum() const;
		void setChecksum( uint16_t ); 
		uint16_t getUrgentPointer() const;
		void setUrgentPointer( uint16_t );
		int getSize() const;
		PacketBuffer makePacket() const;
		bool isTCP() const { return true; }

	private:
		struct my_tcp *header_;
};




#endif 
