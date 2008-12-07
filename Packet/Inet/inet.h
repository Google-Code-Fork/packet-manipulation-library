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

/** \file inet.h
 * This is the declaration for the class Inet 
 */

/** \class Inet 
 * This class is used in conjunction with Packet for handling Inet
 *
 */

#ifndef INET_H 
#define INET_H
#include <stdexcept>
#include "inetData.h"
#include "ipv4.h"
#include "../encapsulateable.h"

class Inet : public Encapsulateable 
{
  public:
    //!constructor
    Inet( )
    {
      header_ = NULL;
    }

    //!builds a Inet object from IPv4
    Inet( const IPv4 &ip )
    {
      header_ = new IPv4( ip );
    }

    //!copy constructor
    Inet( const Inet &n )
    {
      copy( n );
    }

    //!equality operator
    Inet& operator=( const Inet &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
   
    //!destructor
    virtual ~Inet() 
    {
      if( header_ )
      delete header_;
    }

    //!is<some class> returns true if this is of that type 
    //!example: is<IPv4> returns true if IPv4 
    template< class T >bool is( ){ return false; }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: get<IPv4> returns an IPv4 object
    template< class T > T get( ) 
    {
      if( !( is<T>() ) )
      {
	throw std::runtime_error("wrong type");
      }
      return T(*((T*)header_));
    }

    //!sets this inet to be a T
    template< class T > void set( T e )
    {
      if( header_ )
	delete header_;
      header_ = new T;
      *header_ = e;
    }

    //!Makes a PacketBuffer of this Inet
    PacketBuffer makePacket() const 
    {
      return header_->makePacket();
    }

    //!Returns the size of this Inet
    int getSize() const
    {
      return header_->getSize();
    }

  private:
  
    //!Used to copy the different Inet Layers supported
    void copy( const Inet &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isIPv4() )
      {
	header_ = new IPv4( *((IPv4*)n.header_) );
      }
      else
	header_ = NULL;
    }

    //!internal data
    InetData* header_;
};

template<> bool Inet::is<IPv4>( );

#endif
