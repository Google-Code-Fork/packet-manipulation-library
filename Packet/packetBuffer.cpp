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

/** \file packetBuffer.cpp
 * This is the definition for the class PacketBuffer
 */

#include "packetBuffer.h"
#include <iostream>
PacketBuffer::PacketBuffer()
{
  buff_ = NULL;
  size_ = 0;
}

PacketBuffer::PacketBuffer( std::vector< uint8_t > buff )
{
  size_ = buff.size();
  if( size_ == 0 )
  {
    buff_ = NULL;
  }
  else
  {
    buff_ = new uint8_t[ size_ ];
    for( int i=0; i < size_; ++i )
    {
      buff_[i] = buff[i];
    }
  }
}

PacketBuffer::PacketBuffer( const uint8_t* buff, int size )
{
  size_ = size;
  buff_= new uint8_t[ size ];
  for( int i = 0; i < size_; ++i )
  {
    buff_[i] = buff[i];
  }
}

PacketBuffer::~PacketBuffer()
{
  if( buff_ )
    delete [] buff_;
}

PacketBuffer::PacketBuffer( const PacketBuffer& n )
{
  size_ = n.size_;
  if( n.size_ > 0 )
  {
    buff_ = new uint8_t[ n.size_ ];
    for( int i = 0; i < size_; ++i )
    {
      buff_[i] = n.buff_[i];
    }
  }
  else
  {
    buff_ = NULL;
  }
}

PacketBuffer& PacketBuffer::operator=( const PacketBuffer &n )
{
  if( buff_ )
    delete [] buff_;
  if( n.size_ > 0 )
  {
    buff_ = new uint8_t[ n.size_ ];
    size_ = n.size_;
    for( int i = 0; i < size_; ++i )
    {
      buff_[i] = n.buff_[i];
    }
  }
  else
  {
    size_ = 0;
    buff_ = NULL;
  }

  return *this;
}

PacketBuffer& PacketBuffer::operator+=( const PacketBuffer &n )
{
  int newSize = size_ + n.size_;

  uint8_t* newBuff = new uint8_t[ newSize ];
  for( int i = 0; i < size_; ++i )
  {
    newBuff[i] = buff_[i];
  }
  for( int i = size_; i < size_ + n.size_; ++i )
  {
    newBuff[ i ] = n.buff_[ i - size_ ];
  }
  if( buff_ )
    delete [] buff_;
  buff_ = newBuff;
  size_ = newSize;
  return *this;
}

PacketBuffer PacketBuffer::operator+( const PacketBuffer &n )
{
  PacketBuffer result;
  result.size_ = size_ + n.size_;
  result.buff_ = new uint8_t [ result.size_ ];
  for( int i = 0; i < size_; ++i )
  {
    result.buff_[i] = buff_[i];
  }
  for( int i = 0; i < n.size_; ++i )
  {
    result.buff_[size_ + i ] = n.buff_[i];
  }

  return result;

}

void PacketBuffer::setBuffer( std::vector< uint8_t > buff )
{
  if( buff_ )
    delete [] buff_;
  size_ = buff.size();
  buff_ = new uint8_t[ size_ ];
  for( int i = 0; i < size_; ++i )
    buff_[i] = buff[i];
}

void PacketBuffer::setBuffer( uint8_t* buff, int size )
{
  if( buff_ ) 
    delete [] buff_;
  size_ = size; 
  if( size_ > 0 ) 
  {
    buff_ = new uint8_t[ size_ ];
    for( int i = 0; i < size_; ++i )
      buff_[i] = buff[i];
  }
  else
  {
    buff_ = NULL;
  }
}

uint8_t* PacketBuffer::buffer() const
{
  return buff_;
}

int PacketBuffer::size() const
{
  return size_;
}

std::vector< uint8_t > PacketBuffer::vector() const
{
	std::vector< uint8_t > vector;
	for( int i = 0; i < size_; ++i )
	{
		vector.push_back( buff_[i] );
	}
	return vector;
}
