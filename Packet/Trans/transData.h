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

/** \file transData.h
 * This is the declaration for the class TransData 
 */

/** \class TransData
 * This class is used in conjunction with Packet for handling TransData 
 *
 */

#ifndef TRANSDATA_H
#define TRANSDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class TransData : public Encapsulateable
{
  public:
    //!default constructor
    TransData() {}
    //!destructor
    virtual ~TransData(){}
    //!return 0
    virtual int size() const = 0;
    //!returns empty packet buffer
    virtual PacketBuffer makePacket( ) const = 0;
    //!returns false (to be overloaded by TCP)
    virtual bool isTCP() const { return false; }
    //!returns false (to be overloaded by UDP)
    virtual bool isUDP() const { return false; }
};

#endif
