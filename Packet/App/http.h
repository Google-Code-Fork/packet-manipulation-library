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

/** \file http.h
 * This is the declaration for the class for handling HTTP data.
 */

/** \class Raw
 * This class is used in conjunction with Packet for handling HTTP.
 *
 */
#ifndef HTTP_H
#define HTTP_H

#include "appData.h"
#include <vector>

class HTTP : public AppData
{
  public: 
    //!default constructor
    HTTP();
    //!Build a Raw object from a byte buffer
    HTTP( const uint8_t* data, int size );
    //!copy constructor
    HTTP( const HTTP &n );
    //!equality operator
    HTTP& operator=( const HTTP &n );
    //!destructor
    virtual ~HTTP();
    //!Return a Packet Buffer holding the contents of the Raw object for use
    //with other libraries or code
    PacketBuffer makePacket() const;
    //!Return the size of the Raw contents in bytes.
    int size() const;
    //!Set the raw data
    void setData( std::vector< uint8_t > data );
    //!Get the raw data in a std::vector<uint8_t> format
    std::vector< uint8_t > data() const;
    //!Overloaded from App (returns true).
    bool isHTTP() const {return true;}

  private:
    //!internal data
    std::vector<uint8_t> data_;
};

#endif
