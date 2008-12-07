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

/** \file app.h
 * This is the declaration for the class App
 */

/** \class App 
 * This class is used in conjunction with Packet for handling App
 *
 */

#ifndef APP_H 
#define APP_H
#include <stdexcept>
#include "appData.h"
#include "raw.h"
#include "../encapsulateable.h"

class App : public Encapsulateable
{
  public:
    //!default constructor
    App( )
    {
      header_ = NULL;
    }

    //!build an App from a Raw object
    App( const Raw &p )
    {
      header_ = new Raw( p );
    }

    //!copy constructor
    App( const App &n )
    {
      copy( n );
    }

    //!equality operator
    App& operator=( const App &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
   
    //!destructor
    virtual ~App() 
    {
      if( header_ )
      delete header_;
    }

    //!is<some class> returns true if this is of that type 
    //!example: is<Raw> returns true if Raw
    template< class T >bool is( ){ return false; }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: get<Raw> returns a Raw object
    template< class T > T get( ) 
    {
      if( !( is<T>() ) )
      {
	throw std::runtime_error("wrong type");
      }
      return T(*((T*)header_));
    }

    //!sets this App to a T
    template< class T > void set( T e )
    {
      if( header_ )
	delete header_;
      header_ = new T;
      *header_ = e;
    }

    //!returns the size in bytes of the underlying data
    int getSize() const 
    {
      return header_->getSize();
    }

    //!returns a packet buffer of the underlying datatype suitable for other
    //libraries or code
    PacketBuffer makePacket() const 
    {
      return header_->makePacket();
    }

  private:
  
    //!Used to copy different Application layers supported
    void copy( const App &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isRaw() )
      {
	header_ = new Raw( *((Raw*)n.header_) );
      }
      else
	header_ = NULL;
    }

    //!internal data
    AppData* header_;
};

template<> bool App::is<Raw>( );

#endif
