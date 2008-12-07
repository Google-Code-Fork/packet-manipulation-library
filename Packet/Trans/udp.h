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

/** \file udp.h
 * This is the declaration for the class UDP
 */

/** \class UDP 
 * This class is used in conjunction with Packet for handling UDP
 *
 */

#ifndef UDP_H 
#define UDP_H

#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include "transData.h"

struct my_udp {
  //!UDP datatype to be used by the class UDP
	u_int16_t sport; //!source port
	u_int16_t dport; //!destination port
	u_int16_t length; //!length
	u_int16_t checksum; //!checksum
};


class UDP : public TransData
{
  public:
    //!Size of a UDP header in bytes
    static const int UDPSize = 8;

  public:
    //!Default constructor
    UDP();
    //!Build a UDP object from a byte buffer
    UDP( const uint8_t *packet, int size );
    //!Copy constructor
    UDP( const UDP &n );
    //!Equality operator
    UDP& operator =( const UDP &n );

    //!Destructor
    ~UDP();


    //!Returns the sourcePort
    uint16_t getSourcePort() const;
    //!Set the sourcePort
    void setSourcePort( uint16_t );
    //!gets the Destination port
    uint16_t getDestinationPort() const;
    //!sets the Destination port
    void setDestinationPort( uint16_t );
    //!returns the checksum
    uint16_t getChecksum() const;
    //!sets the checksum (doesn't care if it is correct)
    void setChecksum( uint16_t );
    //!gets the length of the UDP header
    uint16_t getLength() const;
    //!sets the length of the UDP header
    void setLength( uint16_t );
    //!returns the size of the UDP header. Overloaded from encapsulatable
    int getSize() const;
    //!Returns a packet buffer for use with other libraries and code
    PacketBuffer makePacket() const;
    //!Returns true... overloaded from TransData
    bool isUDP() const { return true; }

  private:
    //!internal data
    struct my_udp *header_;
};

#endif 
