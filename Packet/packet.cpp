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

/** \file packet.cpp
 * This is the definition for the class Packet 
 */
#include "packet.h"

Packet::Packet()
{
}

Packet::~Packet()
{
}

Packet::Packet( const Packet &p )
{
  linkLayer_ = p.linkLayer_;
  inetLayer_ = p.inetLayer_;
  transLayer_ = p.transLayer_;
  appLayer_ = p.appLayer_;
	timeStamp_ = p.timeStamp_;
}

Packet& Packet::operator=( const Packet &p )
{
  linkLayer_ = p.linkLayer_;
  inetLayer_ = p.inetLayer_;
  transLayer_ = p.transLayer_;
  appLayer_ = p.appLayer_;
	timeStamp_ = p.timeStamp_;

  return *this;
}

Packet& Packet::operator+=( const Packet &n )
{
  std::vector< Link >::const_iterator litr;
  std::vector< Inet >::const_iterator iitr;
  std::vector< Trans >::const_iterator titr;
  std::vector< App >::const_iterator aitr;
  for( litr = n.linkLayer_.begin(); litr != n.linkLayer_.end(); ++litr )
  {
    linkLayer_.push_back( *litr );
  }
  for( iitr = n.inetLayer_.begin(); iitr != n.inetLayer_.end(); ++iitr )
  {
    inetLayer_.push_back( *iitr );
  }
  for( titr = n.transLayer_.begin(); titr != n.transLayer_.end(); ++titr )
  {
    transLayer_.push_back( *titr );
  }
  for( aitr = n.appLayer_.begin(); aitr != n.appLayer_.end(); ++aitr )
  {
    appLayer_.push_back( *aitr );
  }

  return *this;
}

int Packet::size() const
{
  int size = 0;
  std::vector< Link >::const_iterator litr;
  std::vector< Inet >::const_iterator iitr;
  std::vector< Trans >::const_iterator titr;
  std::vector< App >::const_iterator aitr;
  for( litr = linkLayer_.begin(); litr != linkLayer_.end(); ++litr )
  {
    size += litr->size();
  }
  for( iitr = inetLayer_.begin(); iitr != inetLayer_.end(); ++iitr )
  {
    size += iitr->size();
  }
  for( titr = transLayer_.begin(); titr != transLayer_.end(); ++titr )
  {
    size += titr->size();
  }
  for( aitr = appLayer_.begin(); aitr != appLayer_.end(); ++aitr )
  {
    size += aitr->size();
  }
  return size;
}

Packet operator+( const Packet &l, const Packet &r )
{
  Packet tmp( l );
  tmp += r;
  return tmp;
}

PacketBuffer Packet::makePacket() const
{
  PacketBuffer pb;
  //std::vector< uint8_t > packet;
  std::vector< Link >::const_iterator litr;
  std::vector< Inet >::const_iterator iitr;
  std::vector< Trans >::const_iterator titr;
  std::vector< App >::const_iterator aitr;
  for( litr = linkLayer_.begin(); litr != linkLayer_.end(); ++litr )
  {
    pb += litr->makePacket( );
  }
  for( iitr = inetLayer_.begin(); iitr != inetLayer_.end(); ++iitr )
  {
    pb += iitr->makePacket( );
  }
  for( titr = transLayer_.begin(); titr != transLayer_.end(); ++titr )
  {
    pb += titr->makePacket( );
  }
  for( aitr = appLayer_.begin(); aitr != appLayer_.end(); ++aitr )
  {
    pb += aitr->makePacket( );
  }
  return pb;
}

int Packet::linkSize() const
{
  return linkLayer_.size();
}

int Packet::inetSize() const
{
  return inetLayer_.size();
}

int Packet::transSize() const
{
  return transLayer_.size();
}

int Packet::appSize() const
{
  return appLayer_.size();
}

void Packet::clearLink()
{
    linkLayer_.clear();
}

void Packet::clearInet()
{
    inetLayer_.clear();
}

void Packet::clearTrans()
{
    transLayer_.clear();
}

void Packet::clearApp()
{
    appLayer_.clear();
}

void Packet::setTimestamp( const struct timeval &time  )
{
	timeStamp_ = time;
}

struct timeval Packet::timestamp( ) const
{
	return timeStamp_;
}

