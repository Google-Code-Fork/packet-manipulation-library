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

/** \file inetData.h
 * This is the file for the class InetData
 */

/** \class InetData 
 * This class is used in conjunction with Packet for handling InetData 
 */
#ifndef INETDATA_H
#define INETDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"
#include <iostream>

class InetData : public Encapsulateable
{
  public:
    //!Constructor
    InetData() {}
    //!Destructor
    virtual ~InetData() {}
    //!Will be overloaded by the ICMP datatype
    virtual bool isICMP() const { return false; }
    //!Will be overloaded by the IPv4 datatype
    virtual bool isIPv4() const { return false; }
    //!Will be overloaded by the IPv6 datatype
    //!This is a stub as the IPv6 datatype doesn't exist yet
    virtual bool isIPv6() const { return false; }
    //!Pure Function
    virtual int size() const = 0;
    //!returns an empty buffer
    virtual PacketBuffer makePacket() const = 0;
};

#endif
