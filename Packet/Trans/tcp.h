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

/** \file tcp.h
 * This is the declaration for the class TCP 
 */

/** \class TCP 
 * This class is used in conjunction with Packet for handling TCP 
 *
 */



#ifndef TCP_H 
#define TCP_H

#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include "transData.h"

struct my_tcp {
  //!TCP datatype for use with the class TCP
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
  //!Size of the TCP data type used in TCP
  static const uint8_t TCPStructSize=20; //size of the above struct
  public:

  //!default constructor
  TCP();
  //!build a TCP object from a byte buffer
  TCP( const uint8_t *packet, int size );
  //!copy constructor
  TCP( const TCP &n );
  //!equality operator
  TCP& operator =( const TCP &n );
  //!destructor
  ~TCP();

  //!return the source port
  uint16_t getSourcePort() const;
  //!set the source port
  void setSourcePort( uint16_t );
  //!return the destination port
  uint16_t getDestinationPort() const;
  //!set the destination port
  void setDestinationPort( uint16_t );
  //!return the sequence number
  uint32_t getSequenceNumber() const;
  //!set the sequence number
  void setSequenceNumber( uint32_t );
  //!return the acknowledgement number
  uint32_t getAcknowledgementNumber() const;
  //!set the acknowledgement number
  void setAcknowledgementNumber( uint32_t );
  //!return the data offset
  uint8_t getDataOffset() const;
  //!set the data offset
  void setDataOffset( uint8_t );
  //!return the flage (true|false)
  bool getFlagsCWR() const;
  //!set the flag (true|false)
  void setFlagsCWR( bool );
  //!set the flag true
  void setFlagsCWR( ); // ==setFlagsCWR( true );
  //!return the flage (true|false)
  bool getFlagsECE() const;
  //!set the flag (true|false)
  void setFlagsECE( bool );
  //!set the flag true
  void setFlagsECE( ); // == setFlagsECE( true );
  //!return the flage (true|false)
  bool getFlagsURG() const;
  //!set the flag (true|false)
  void setFlagsURG( bool );
  //!set the flag true
  void setFlagsURG( ); // == setFlagsURG( true );
  //!return the flage (true|false)
  bool getFlagsACK() const;
  //!set the flag (true|false)
  void setFlagsACK( bool );
  //!set the flag true
  void setFlagsACK( ); // == setFlagsACK( true );
  //!return the flage (true|false)
  bool getFlagsPSH() const;
  //!set the flag (true|false)
  void setFlagsPSH( bool );
  //!set the flag true
  void setFlagsPSH( ); // == setFlagsPSH( true );
  //!return the flage (true|false)
  bool getFlagsRST() const;
  //!set the flag (true|false)
  void setFlagsRST( bool );
  //!set the flag true
  void setFlagsRST( ); // == setFlagsRST( true );
  //!return the flage (true|false)
  bool getFlagsSYN() const;
  //!set the flag (true|false)
  void setFlagsSYN( bool );
  //!set the flag true
  void setFlagsSYN( ); // == setFlagsSYN( true );
  //!return the flage (true|false)
  bool getFlagsFIN() const;
  //!set the flag (true|false)
  void setFlagsFIN( bool );
  //!set the flag true
  void setFlagsFIN( ); // == setFlagsFIN( true );
  //!return the window size
  uint16_t getWindow() const;
  //!set the window size
  void setWindow( uint16_t ); 
  //!return the checksum
  uint16_t getChecksum() const;
  //!set the checksum
  void setChecksum( uint16_t ); 
  //!return the urgent pointer
  uint16_t getUrgentPointer() const;
  //!set the urgent pointer
  void setUrgentPointer( uint16_t );
  //!return the size of the tcp header
  int getSize() const;
  //!return a Packet buffer of the TCP header suitable for use in other libraries and code
  PacketBuffer makePacket() const;
  //!return true... overloaded from TransData
  bool isTCP() const { return true; }

  private:
  //!internal data
  struct my_tcp *header_;
};




#endif 
