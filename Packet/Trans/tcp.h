/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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
#include "../../common/smartPtr.h"
#include "tcpOptions.h"
#include "eolOption.h"
#include "mssOption.h"
#include "noopOption.h"
#include "sackOption.h"
#include "sackPermittedOption.h"
#include "timeStampOption.h"
#include "wsOption.h"
#include "../Inet/ipv4.h"
#include "../Inet/ipv6.h"

struct my_tcp {
  //!TCP datatype for use with the class TCP
  u_int16_t sport; //source port
  u_int16_t dport; //destination port
  u_int32_t sequenceNumber; 
  u_int32_t ackNumber;
  u_int8_t dataOffset;
  #define X2(tcp) ((tcp)->dataOffset & 0x0FU)
  #define OFFSET(tcp)  (((tcp)->dataOffset & 0xF0U) >> 4U)
  u_int8_t flags;
  #define TCP_CWR 0x80U
  #define TCP_ECE 0x40U
  #define TCP_URG 0x20U
  #define TCP_ACK 0x10U
  #define TCP_PSH 0x08U
  #define TCP_RST 0x04U
  #define TCP_SYN 0x02U
  #define TCP_FIN 0x01U
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
  uint16_t sourcePort() const;
  //!set the source port
  void setSourcePort( uint16_t );
  //!return the destination port
  uint16_t destinationPort() const;
  //!set the destination port
  void setDestinationPort( uint16_t );
  //!return the sequence number
  uint32_t sequenceNumber() const;
  //!set the sequence number
  void setSequenceNumber( uint32_t );
  //!return the acknowledgement number
  uint32_t acknowledgementNumber() const;
  //!set the acknowledgement number
  void setAcknowledgementNumber( uint32_t );
  //!return the data offset
  uint8_t dataOffset() const;
  //!set the data offset
  void setDataOffset( uint8_t );
  //!returns reserved data after the dataoffset in tcp header
  uint8_t x2() const;
  //!sets the reserved data after the dataoffset in the tcp header
  void setX2( uint8_t x2 );
  bool flags( const uint8_t &mask ) const;
  //!return the flage (true|false)
  bool CWR_Flag() const;
  //!set the flag (true|false)
  void setCWR_Flag( bool );
  //!set the flag true
  void setCWR_Flag( ); // ==setFlagsCWR( true );
  //!return the flage (true|false)
  bool ECE_Flag() const;
  //!set the flag (true|false)
  void setECE_Flag( bool );
  //!set the flag true
  void setECE_Flag( ); // == setFlagsECE( true );
  //!return the flage (true|false)
  bool URG_Flag() const;
  //!set the flag (true|false)
  void setURG_Flag( bool );
  //!set the flag true
  void setURG_Flag( ); // == setFlagsURG( true );
  //!return the flage (true|false)
  bool ACK_Flag() const;
  //!set the flag (true|false)
  void setACK_Flag( bool );
  //!set the flag true
  void setACK_Flag( ); // == setFlagsACK( true );
  //!return the flage (true|false)
  bool PSH_Flag() const;
  //!set the flag (true|false)
  void setPSH_Flag( bool );
  //!set the flag true
  void setPSH_Flag( ); // == setFlagsPSH( true );
  //!return the flage (true|false)
  bool RST_Flag() const;
  //!set the flag (true|false)
  void setRST_Flag( bool );
  //!set the flag true
  void setRST_Flag( ); // == setFlagsRST( true );
  //!return the flage (true|false)
  bool SYN_Flag() const;
  //!set the flag (true|false)
  void setSYN_Flag( bool );
  //!set the flag true
  void setSYN_Flag( ); // == setFlagsSYN( true );
  //!return the flage (true|false)
  bool FIN_Flag() const;
  //!set the flag (true|false)
  void setFIN_Flag( bool );
  //!set the flag true
  void setFIN_Flag( ); // == setFlagsFIN( true );
  //!return the window size
  uint16_t windowSize() const;
  //!set the window size
  void setWindowSize( uint16_t ); 
  //!return the checksum
  uint16_t checksum() const;
  //!set the checksum
  void calculateChecksum( const IPv4 &ip, const PacketBuffer &data );
  void calculateChecksum( const IPv6 &ip, const PacketBuffer &data );
  //!set the checksum
  void setChecksum( uint16_t ); 
  //!return the urgent pointer
  uint16_t urgentPointer() const;
  //!set the urgent pointer
  void setUrgentPointer( uint16_t );
  //!return the size of the tcp header
  int size() const;
  //!return a Packet buffer of the TCP header suitable for use in other libraries and code
  PacketBuffer makePacket() const;
  //!return true... overloaded from TransData
  bool isTCP() const { return true; }

	//OPTIONS
	//! Erase all options.
	void clearOptions() { options_.clear(); }
	//! Add a new option to the list of options.
	void addOption( SmartPtr< TCPOption > option );
	//! Return the current list of options. 
	std::vector< SmartPtr< TCPOption > > options() const { return options_; }

  private:
  //!internal data
  struct my_tcp *header_;
	std::vector< SmartPtr< TCPOption > > options_;
};

#endif 
