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

/** \file appData.h
 * This is the declaration for the class App
 */

/** \class AppData 
 * This class is used in conjunction with Packet for handling App
 *
 */

#ifndef APPDATA_H
#define APPDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class AppData : public Encapsulateable
{
  public:
    //!constructor
    AppData() {}
    //!destructor
    virtual ~AppData() {}
    //!Returns 0
    virtual int size() const { return 0; }
    //!Return empty PacketBuffer
    virtual PacketBuffer makePacket() const { return PacketBuffer(); }
    //!Raw Overloads this, returns false;
    virtual bool isRaw() const {return false;}
		//!HTTP Overloads this, return false;
		virtual bool isHTTP() const {return false;}
    //!Packet Overloads this, returns false;
    virtual bool isPacket() const { return false; }
};

#endif
