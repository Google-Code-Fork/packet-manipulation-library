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

/** \file linkData.h
 * This is the declaration for the class for handling ethernet frames 
 */

/** \class LinkData
 * This class is used in conjunction with Packet for handling Link Layer frames.
 */

#ifndef LINKDATA_H
#define LINKDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class LinkData : public Encapsulateable  
{
  public:
    //!Default Constructor
    LinkData(){ }
    //!Destructor
    virtual ~LinkData() {}
    //!Returns false - Acts as an interface and the Ethernet class overloads
    //this function
    virtual bool isEthernet() const { return false; }
    //!Returns false - Acts as an interface and the Mac class overloads
    //this function
    virtual bool isMac() const { return false; }
    //!Returns an empty packet buffer
    virtual PacketBuffer makePacket() const { return PacketBuffer(); }
    //!Returns 0
    virtual int size() const { return 0; } //should be defined by base class//{ return 0; }
};


#endif
