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

/** \file packetBuilder.cpp
 * This is the definition for the class PacketBuilder
 */
#include "packetBuilder.h"

//template specialization must go outside of class def
template <> Packet PacketBuilder::build<Ethernet>( const uint8_t* buff, int size )
{
  Ethernet e( buff, size );
  Packet p;
  p.pushBackLink( e );
  const uint8_t* newbuff = buff + e.size();
  int newsize = size - e.size();
  Packet p2;
  switch( e.type() )
  {
    case ethernetProtocol::k_ip:
      //std::cerr << "IP" << std::endl;
      p2 = build< IPv4 >( newbuff, newsize );
      break;
    case ethernetProtocol::k_ipv6:
      //std::cerr << "IPv6" << std::endl;
      p2 = build< IPv6 >( newbuff, newsize );
      break;
    case ethernetProtocol::k_arp:
      p2 = build< Arp >( newbuff, newsize );
      //std::cerr << "ARP" << std::endl;
      //placeholder
      break;
    default:
      //std::cerr << "RAW" << std::endl;
      p2 = build< Raw >( newbuff, newsize );
      break;
  }
  return p + p2;
}

template <> Packet PacketBuilder::build< Arp >( const uint8_t* buff, int size )
{
  Arp arp( buff, size );
  Packet p;
  p.pushBackApp( arp );
  const uint8_t* newbuff = buff + p.size();
  int newsize = size - p.size();
  Packet p2;
  if( newsize > 0 )
    p2 = build< Raw >( newbuff, newsize );

  return p + p2;
}

template <> Packet PacketBuilder::build<IPv4>( const uint8_t* buff, int size )
{
  IPv4 ip( buff, size );
  Packet p; 
  p.pushBackInet( ip );
  Packet p2;
  const uint8_t* newbuff = buff + p.size();
  int newsize = size - p.size();
  
  switch( static_cast<uint16_t>( ip.protocol() ) )
  {
    case ipProtocol::TCP:
      p2 = build< TCP >( newbuff, newsize );
      break;
    case ipProtocol::UDP:
      p2 = build< UDP >( newbuff, newsize );
      break;
    default:
      p2 = build< Raw >( newbuff, newsize );
  }

  return p + p2;
}

template <> Packet PacketBuilder::build<IPv6>( const uint8_t* buff, int size )
{
  IPv6 ip(buff, size );
  Packet p;
  p.pushBackInet( ip );
  Packet p2;
  const uint8_t* newbuff = buff + p.size();
  int newsize = size - p.size();

  switch( static_cast<uint16_t>( ip.nextHeader() ) )
  {
    case ipProtocol::TCP:
      p2 = build< TCP >( newbuff, newsize );
      break;
    case ipProtocol::UDP:
      p2 = build< UDP >( newbuff, newsize );
      break;
    default:
      p2 = build< Raw >( newbuff, newsize );
  }

  return p + p2;
}

template <> Packet PacketBuilder::build<TCP>( const  uint8_t* buff, int size )
{
  TCP tcp( buff, size );
  Packet p; 
  p.pushBackTrans( tcp );
  Packet p2;
  const uint8_t* newbuff = buff + tcp.size();
  int newsize = size - tcp.size();

  if( tcp.sourcePort() == 53 || tcp.destinationPort() == 53 )
	{ //DNS
		p2 = build< DNS >( newbuff, newsize );
	}
	else
	{
		p2 = build< Raw >( newbuff, newsize );
	}

  return p + p2;
}

template <> Packet PacketBuilder::build<UDP>( const  uint8_t* buff, int size )
{
  UDP udp( buff, size );
  Packet p; 
  p.pushBackTrans( udp );
  Packet p2;
  const uint8_t* newbuff = buff + udp.size();
  int newsize = size - udp.size();

	if( udp.sourcePort() == 53 || udp.destinationPort() == 53 )
	{ //DNS
		p2 = build< DNS >( newbuff, newsize );
	}
	else
	{
		p2 = build< Raw >( newbuff, newsize );
	}

  return p + p2;
}

template <> Packet PacketBuilder::build<Raw>( const  uint8_t* buff, int size )
{
  Raw r( buff, size );
  Packet p;
  p.pushBackApp( r );

  return p;
}

template <> Packet PacketBuilder::build<DNS>( const uint8_t* buff, int size )
{
	DNS dns( buff, size );
	Packet p;
	p.pushBackApp( dns );

	return p;
}

