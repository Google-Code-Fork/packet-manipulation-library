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

/** \file trans.h
 * This is the declaration for the class Trans 
 */

/** \class Trans 
 * This class is used in conjunction with Packet for handling Trans
 *
 */

#ifndef TRANS_H
#define TRANS_H
#include <stdexcept>
#include "transData.h"
#include "tcp.h"
#include "udp.h"
#include "../encapsulateable.h"

class Trans : public Encapsulateable
{
  public:
    //!Default constructor
    Trans( )
    {
      header_ = NULL;
    }

    //!Build a Trans object from a TCP one
    Trans( const TCP &tcp )
    {
      header_ = new TCP( tcp );
    }
   
    //!Build a Trans object from a UDP one
    Trans( const UDP &udp )
    {
      header_ = new UDP( udp );
    }

    //!Copy constructor
    Trans( const Trans &n )
    {
      copy( n );
    }

    //!equality operator
    Trans& operator=( const Trans &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
   
    //!destructor
    virtual ~Trans() 
    {
      if( header_ )
      delete header_;
    }
    
    //!is<some class> returns true if this is of that type 
    //!example: is<TCP> returns true if TCP 
		//is<UDP> and is<TCP> Declared below
    template< class T >bool is( ) const { return false; }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: get<TCP> returns a TCP object
		template< class T > T get( ) 
		{
			if( !( is<T>() ) )
			{
				throw std::runtime_error("wrong type");
			}
			return T(*((T*)header_));
		}

		//!sets this trans to be T
		template< class T > void set( T e )
		{
			if( header_ )
				delete header_;
			header_ = new T;
			*header_ = e;
		}

		//!returns the size in bytes of the underlying data
		int size() const 
		{
			return header_->size();
		}

		//!returns a packet buffer of the underlying datatype suitable for other
		//libraries or code
		PacketBuffer makePacket() const 
		{
			return header_->makePacket();
		}


	private:

		//!Used to copy different Transport Layers supported
		void copy( const Trans &n )
		{
			if( n.header_ == NULL )
			{
				header_ = NULL;
			}
			else if( n.header_->isTCP() )
			{
				header_ = new TCP( *((TCP*)n.header_) );
			}
			else if( n.header_->isUDP() )
			{
				header_ = new UDP( *((UDP*)n.header_) );
			}
			else
				header_ = NULL;
		}

		//!internal data
		TransData* header_;
};

template<> bool Trans::is<UDP>( ) const;

template<> bool Trans::is<TCP>( ) const;



#endif
