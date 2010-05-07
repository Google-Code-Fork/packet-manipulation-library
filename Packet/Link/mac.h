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

/** \file mac.h
 * This is the declaration for the class for handling MAC addresses
 */

/** \class MACAddress
 * This class is used in conjunction with Ethernet for handling MAC addresses
 */

#ifndef MAC_H
#define MAC_H

#include "linkData.h"
#include <string>
#include <vector>

class MACAddress : public LinkData
{
  public: //constants
    //! Size of a MAC address in bytes
    static const int MACAddressSize = 6;

  public: 
    //! Default Constructor
    MACAddress();
    //! Builds a MACAddress with the bytes in mac
    MACAddress( uint8_t mac[MACAddressSize] );
    //! Builds a MACAddress with the bytes in mac
    MACAddress( std::vector< uint8_t > mac );
    //! Copy Constructor
    MACAddress( const MACAddress& a );
    //! Assignment operator
    MACAddress& operator=( const MACAddress &a );
		//! Equality operation
		bool operator==( const MACAddress &a );
    //! Destructor
    virtual ~MACAddress();

    //! Sets the address base on the bytes in mac
    void setMACAddress( std::vector< uint8_t > mac );
    //! Returns the size of a MAC address
    int getSize() const;
    //! Returns a Packetbuffer with the MAC address
    PacketBuffer makePacket() const;
    //! Places the mac address in the array mac
    void getMAC( uint8_t (&mac)[MACAddressSize]);//puts the mac address in the memory mac
    //! returns true
    bool isMac() const;

  private:
    //!Private data of MACAddress
    std::vector< uint8_t > mac_;
};
#endif
