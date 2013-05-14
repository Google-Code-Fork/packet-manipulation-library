/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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

/** \file packetBuffer.h
 * This is the declaration for the class PacketBuffer
 */

/** \class PacketBuffer 
 * This class is used in conjunction with Packet library
 * Provides access to byte buffers and keeps track of size
 * This is mainly for internal use but in the case of make packet can be used to
 * provide your own interface to the Packet class..
 */
#ifndef PACKETBUFFER_H
#define PACKETBUFFER_H

#include <vector>
#include <stdint.h>

class PacketBuffer 
{
  public:
    //!Default constructor
    PacketBuffer();
    //!Builds a Packet Buffer from a vector instead of a buffer
    PacketBuffer( std::vector< uint8_t > );
    //!Builds a Packet Buffer from a buffer
    PacketBuffer( const uint8_t* buff, int size );
    //!Destructs a PacketBuffer
    ~PacketBuffer();
    //!Copy constructor
    PacketBuffer( const PacketBuffer& n );
    //!Equality operator
    PacketBuffer& operator=( const PacketBuffer &n );
    //!Allows concatenation of Packetbuffers
    PacketBuffer& operator+=( const PacketBuffer &n );
    //!Add buffers
    PacketBuffer operator+( const PacketBuffer &n );
    //!sets the buffer to the contents of buff
    void setBuffer( std::vector< uint8_t > buff );
    //!sets the buffer to the contents of buff
    void setBuffer( uint8_t* buff, int size );
    //!returns a pointer to the buffer (only lives as long as the Packet Buffer
    //so be careful...
    uint8_t* buffer() const;
    //!Returns the size...
    int size() const;
		std::vector< uint8_t > vector() const;

  private:
    //!Internal Data
    uint8_t* buff_;
    //!Internal Data
    int size_;
};

#endif
