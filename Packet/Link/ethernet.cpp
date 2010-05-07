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

/** \file ethernet.cpp
 * This is definition for the class for handling ethernet frames 
 */


#include <stdexcept>
#include "ethernet.h"
#include "mac.h"
#include <netinet/in.h>

Ethernet::Ethernet()
{
  MACAddress mac; //zero everything out
  mac.getMAC( header_.destination);
  mac.getMAC( header_.source );
  header_.protocol = ethernetProtocol::ETH_P_IP; //default to IP
}

Ethernet::Ethernet( const Ethernet& n )
{
	header_ = n.header_;
	vlanTag_ = n.vlanTag_;
}

Ethernet::Ethernet( const uint8_t* buff, int size )
{
  if( size < EthernetSize )
    throw std::runtime_error( "Not enough to generate ethernet header" );
  header_ = *((EthernetHeader*)buff);
  if( header_.protocol == ethernetProtocol::ETH_P_8021Q )
  {
    //check to make sure the buff is big enough
    if( size < (EthernetSize + Dot1QSize) )
    {
      throw std::runtime_error( "Not enough buffer for Dot1Q packet" );
    }
    const uint8_t* ptr = buff + EthernetSize;
    vlanTag_ = *((VlanTag*)ptr);
  }
}

Ethernet::Ethernet( const std::vector< uint8_t > &bytes )
{
	
}

Ethernet& Ethernet::operator =( const Ethernet &n )
{
  header_ = n.header_;
  vlanTag_ = n.vlanTag_;
}

Ethernet::~Ethernet()
{
}

MACAddress Ethernet::getDestinationMAC()
{
  return MACAddress( header_.destination );
}

void Ethernet::setDestinationMAC( MACAddress mac )
{
  mac.getMAC( header_.destination );
}

MACAddress Ethernet::getSourceMAC()
{
  return MACAddress( header_.source );
}

void Ethernet::setSourceMAC( MACAddress mac )
{
  mac.getMAC( header_.source );
}

uint16_t Ethernet::getType()
{
	return header_.protocol;
}

void Ethernet::setType( uint16_t type )
{
	header_.protocol =  type;
}

uint16_t Ethernet::getDot1QType( )
{
  if( header_.protocol != ethernetProtocol::ETH_P_8021Q )
    throw std::runtime_error( "not 802.1Q" );

  return vlanTag_.type;
}

void Ethernet::setDot1QType( uint16_t type )
{
  header_.protocol = ethernetProtocol::ETH_P_8021Q; //this is the only way this is valid.
  vlanTag_.type = type;
}

int Ethernet::getSize() const
{
  if( header_.protocol == ethernetProtocol::ETH_P_8021Q )
    return EthernetSize + Dot1QSize;
  return EthernetSize;
}

PacketBuffer Ethernet::makePacket() const
{
  int size = EthernetSize;
  if( header_.protocol == ethernetProtocol::ETH_P_8021Q )
    size += Dot1QSize;
  uint8_t* buff = new uint8_t[size];
  *((EthernetHeader*)buff) = header_;
  if( header_.protocol == ethernetProtocol::ETH_P_8021Q )
    *((VlanTag*)(buff+EthernetSize)) = vlanTag_;
  
  return PacketBuffer( buff, size );
}

bool Ethernet::isEthernet() const
{
  return true;
}
