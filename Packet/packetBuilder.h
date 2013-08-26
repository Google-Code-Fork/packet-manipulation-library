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

/** \file packetBuilder.h
 * This is the declaration for the class PacketBuilder
 */

/** \class PacketBuilder 
 * This class builds objects of type Packet
 */
#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "packet.h"
#include "Link/ethernet.h"
#include "Inet/ipv4.h"
#include "Inet/icmp.h"
#include "Inet/ipv6.h"
#include "Trans/tcp.h"
#include "Trans/udp.h"
#include "App/raw.h"
#include "App/dnsPacket.h"

class PacketBuilder
{
  public:
    //!default constructor
    PacketBuilder(  ) {}
    //!destructor
    virtual ~PacketBuilder(){}

    //!builds a packet starting from the T header from a byte buffer given as a
    //!PacketBuffer
    template <class T> Packet buildPacket( PacketBuffer pb ) { return build< T >( pb.buffer(), pb.size() ); }
    //!Builds Packet from a buffer and a size
    template <class K> Packet build( const uint8_t* buff, int size );
    //!Builds a response packet based on an incomming packet. (Switches mac addresses, ip address, ports, sequence, etc... )
    template <class K> Packet buildResponse( const Packet &p );
};

//template specialization must go outside of class def
template <> Packet PacketBuilder::build<DNS>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<Raw>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<UDP>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<TCP>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<Ethernet>( const uint8_t* buff, int size );
template <> Packet PacketBuilder::build<IPv4>( const uint8_t* buff, int size );
template <> Packet PacketBuilder::build<IPv6>( const uint8_t* buff, int size );
template <> Packet PacketBuilder::build<Arp>( const uint8_t* buff, int size );

template <> Packet PacketBuilder::buildResponse< DNS >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< TCP >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< UDP >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< Ethernet >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< IPv4 >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< ICMP >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< Arp >( const Packet &p );
template <> Packet PacketBuilder::buildResponse< IPv6 >( const Packet &p );
#endif
