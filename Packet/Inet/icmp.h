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

/** \file icmp.h
 * This is the declaration for the class ICMP 
 */

/** \class ICMP 
 * This class is used in conjunction with Packet for handling ICMP
 *
 */



#ifndef ICMP_H
#define ICMP_H


#include <stdexcept>
#include <netinet/in.h>
#include "../packet.h"
#include "inetData.h"

typedef struct icmpHeader 
{
  //! icmp header data for use in the class ICMP
  uint8_t type;
  uint8_t code;
  uint16_t checkSum;
} icmpHeader;

typedef struct icmpRequest
{
  //! icmpRequest data for use in ICMP
  uint16_t identifier;
  uint16_t sequence;
}icmpRequest;

class Packet;

//!helper function for calculating checksums
uint16_t icmpChecksum (uint16_t * buffer, int numOfBytes );

class ICMP : public InetData
{
  public:
    //!constructor
    ICMP();
    //!destructor
    ~ICMP();
    //!construcot ICMP object from buffer
    ICMP( const uint8_t *packet, const int size );
    //!copy constructor
    ICMP( const ICMP &n );
    //! equality operator
    ICMP& operator= ( const ICMP &n );

    //!Return the ICMP type
    uint8_t getType() const;
    //!Set the ICMP type
    void setType(uint8_t type);
    //!Return the ICMP code
    uint8_t getCode() const;
    //!set the ICMP code
    void setCode(uint8_t code);
    //!return the checksum field
    uint16_t getChecksum() const;
    //!set the checksum
    void setChecksum( uint16_t );

    //!return the length of the header
    int getHeaderLength() const;

    //!if a type 8 icmp request
    uint16_t getIdentifier() const;
    //!to set a type 8 icmp request
    void setIdentifier( uint16_t ident );
    //!return squence number
    uint16_t getSequenceNum() const;
    //!set the squence number
    void setSequenceNum( uint16_t sequence );
    //!generate the checksum
    void generateChecksum();

    //!This is for type 11 icmp time-to-live exceeded 
    //!Returns a Packet object with the orginal content of the the exceeded
    //packet.
    Packet getOrginalPacket();

    //!Returns a PacketBuffer for use with other libraries and code
    PacketBuffer make Packet() const;
    //!Returns the size in bytes of the ICMP header
    int getSize() const;
    //!Returns true... overloaded from InetData
    bool isICMP() const { return true; }

  private:
    //!internal data
    icmpHeader *header_;//All icmp packets :)
    //!internal data
    icmpRequest *request_; //type 8
    //!internal data
    uint8_t *orginal_; //type 11 copy of orginal packet ip header
};

#endif
