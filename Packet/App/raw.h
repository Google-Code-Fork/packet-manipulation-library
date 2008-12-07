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

/** \file raw.h
 * This is the declaration for the class for handling Raw data
 * This is a catch all class. This is also how the packet class can currently
 * support unknown protocols. Unknown as in they are yet supported in PacMan. :)
 */

/** \class Raw
 * This class is used in conjunction with Packet for handling anything.
 *
 */
#ifndef RAW_H
#define RAW_H

#include "appData.h"
#include <vector>

class Raw : public AppData
{
  public: 
    //!default constructor
    Raw();
    //!Build a Raw object from a byte buffer
    Raw( const uint8_t* data, int size );
    //!copy constructor
    Raw( const Raw &n );
    //!equality operator
    Raw& operator=( const Raw &n );
    //!destructor
    virtual ~Raw();
    //!Return a Packet Buffer holding the contents of the Raw object for use
    //with other libraries or code
    PacketBuffer makePacket() const;
    //!Return the size of the Raw contents in bytes.
    int getSize() const;
    //!Set the raw data
    void setData( std::vector< uint8_t > data );
    //!Get the raw data in a std::vector<uint8_t> format
    std::vector< uint8_t > getData() const;
    //!Overloaded from App (returns true).
    bool isRaw() const {return true;}

  private:
    //!internal data
    std::vector<uint8_t> data_;
};

#endif
