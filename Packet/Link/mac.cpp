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

/** \file mac.cpp
 * This is the definition for the class for handling MAC addresses
 */

#include <stdexcept>
#include "mac.h"

MACAddress::MACAddress() : mac_( std::vector< uint8_t >(6,0) )
{
}

MACAddress::MACAddress( uint8_t mac[MACAddressSize] ) : mac_( std::vector< uint8_t >(6,0) )
{
  mac_[0] = mac[0];
  mac_[1] = mac[1];
  mac_[2] = mac[2];
  mac_[3] = mac[3];
  mac_[4] = mac[4];
  mac_[5] = mac[5];
}

MACAddress::MACAddress( std::vector< uint8_t > mac ) : mac_( std::vector< uint8_t >(6,0) )
{
  if( mac.size() != 6 )
    throw std::runtime_error( "Mac Address Size Incorrect" );
  mac_ = mac;
}

MACAddress::MACAddress( const MACAddress &a ) 
{
  mac_ = a.mac_; 
}

MACAddress& MACAddress::operator=( const MACAddress &a )
{
  mac_ = a.mac_;
  return *this;
}

MACAddress::~MACAddress()
{
}

void MACAddress::setMACAddress( std::vector< uint8_t > mac )
{
  if( mac.size() != 6 )
  {
    throw std::runtime_error( "Invalid MAC address" );
  }
  mac_ = mac;
}

int MACAddress::getSize() const
{
  return MACAddressSize;
}

PacketBuffer MACAddress::makePacket(  ) const
{
  return PacketBuffer( mac_ );
}

void MACAddress::getMAC( uint8_t (&macPtr)[MACAddressSize] )
{
  macPtr[0] = mac_[0];
  macPtr[1] = mac_[1];
  macPtr[2] = mac_[2];
  macPtr[3] = mac_[3];
  macPtr[4] = mac_[4];
  macPtr[5] = mac_[5];
}

bool MACAddress::isMac() const
{
  return true;
}
