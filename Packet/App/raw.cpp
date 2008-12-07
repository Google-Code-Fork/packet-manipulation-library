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

/** \file raw.cpp
 * This is the definition for the class for handling Raw data
 * This is a catch all class. This is also how the packet class can currently
 * support unknown protocols. Unknown as in they are yet supported in PacMan. :)
 */
#include "raw.h"

Raw::Raw()
{
}

Raw::Raw( const uint8_t* data, int size )
{
  for( int i = 0; i < size; ++i )
  {
    data_.push_back( data[i] );
  }
}

Raw::Raw( const Raw &n )
{
  data_ = n.data_;
}

Raw& Raw::operator=( const Raw &n )
{
  data_ = n.data_;
  return *this;
}

Raw::~Raw()
{
}

PacketBuffer Raw::makePacket() const
{
  return PacketBuffer( data_ );
}

int Raw::getSize() const
{
  return data_.size();
}

void Raw::setData( std::vector< uint8_t > data )
{
  data_ = data;
}

std::vector< uint8_t > Raw::getData() const
{
  return data_;
}
