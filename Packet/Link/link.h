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

/** \file link.h
 * This is the declaration for the class Link
 */

/** \class Link 
 * This class is used in conjunction with Packet for handling link layer
 *
 */


#ifndef LINK_H
#define LINK_H
#include <stdexcept>
#include "../encapsulateable.h"
#include "linkData.h"
#include "ethernet.h"

class Link : public Encapsulateable
{
  public:
    //! Constructor
    Link( )
    {
      header_ = NULL;
    }

    //! Build a Link from an Ethernet object
    Link( const Ethernet &e )
    {
      header_ = new Ethernet;
      *header_ = e;
    }

    //! Build a Link from a MACAddress object
    Link( const MACAddress &m )
    {
      header_ = new MACAddress;
      *header_ = m;
    }

    //!copy constructor
    Link( const Link &n )
    {
      copy( n );
    }

    //!Equality operator
    Link& operator=( const Link &n )
    {
      if( header_ )
				delete header_;
      copy( n );
      return *this;
    }
   
    //!Destructor
    virtual ~Link() 
    {
      //if( header_ )
      delete header_;
    }

    //!is<some class> returns true if this is of that type 
    //!example: is<Ethernet> returns true if Ethernet
    template< class T >bool is( ) const { return false; }
   
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: get<Ethernet> returns an Ethernet object
    template< class T > T get( ) 
    {
      if( !( is<T>() ) )
      {
				throw std::runtime_error("wrong type");
      }
      return T(*((T*)header_));
    }

    //!Sets this link to be a T
    template< class T > void set( T e )
    {
      if( header_ )
				delete header_;
      header_ = new T;
      *header_ = e;
    }

    //!Makes a PacketBuffer of this Link
    PacketBuffer makePacket() const
    {
      return header_->makePacket();
    }

    //!Returns the size of this Link
    int size() const
    {
      return header_->size();
    }

  private:
  
    //!Used to copy different Link Layers supported
    void copy( const Link &n )
    {
      if( n.header_ == NULL )
			{
				header_ = NULL;
			}
			else if( n.header_->isEthernet() )
			{
				header_ = new Ethernet( *((Ethernet*)n.header_) );
			}
			else if( n.header_->isMac() )
			{
				header_ = new MACAddress( *((MACAddress*)n.header_) );
			}
			else
				header_ = NULL;
		}

		//!internal data
		LinkData* header_;
};

template<> bool Link::is<Ethernet>( ) const;

#endif
