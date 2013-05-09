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

/** \file packet.h
 * This is the declaration for the class Packet
 */

/** \class Packet 
 * This class is the main interface for the Packet library
 */

#ifndef PACKET_H
#define PACKET_H

#include "encapsulateable.h"
#include "packetBuffer.h"
#include "Link/link.h"
#include "App/app.h"
#include "Inet/inet.h"
#include "Trans/trans.h"
#include <vector>
#include <stdexcept>
#include <sys/time.h>

class Packet : public AppData
{
  public:
    //!Default constructor
    Packet();
    //!copy constructor
    Packet( const Packet &n );
    //!Equality operator
    Packet& operator=( const Packet &n );
    //!Destructor
    ~Packet();
    //!This is NOT concatentation. This operator takes all the layers of n and
    //attaches them to the current packet. This makes this more of a merge but
    //it a very useful operation in packet construction. To see a use case look
    //at the PacketBuilder code in packetBuilder.cpp
    Packet& operator+=( const Packet &n );

    //!Returns a PacketBuffer with the contents of the packet
    PacketBuffer makePacket() const;
    //!Returns the size of the packet in bytes
    int size() const;
  
    //!Puts a link layer header on the link layer 
    template<class T> void pushBackLink( T l )
    {
      linkLayer_.push_back( Link( l ) );
    }

    //!Puts a internet layer header on the inet layer
    template<class T> void pushBackInet( T i )
    {
      inetLayer_.push_back( Inet( i ));
    }

    //!Puts a transport layer header on the trans laye
    template<class T > void pushBackTrans( T t )
    {
      transLayer_.push_back( Trans( t ) );
    }

    //!Puts application layer data on the application layer 
    template < class T > void pushBackApp( T a )
    {
      appLayer_.push_back( App( a ) );
    }

    //!is<some class> returns true if this is of that type 
    //!example: linkIs<Ethernet> returns true if Ethernet
    template < class T > bool linkIs( uint32_t i = 0 ) const
    {
			if( i >= linkLayer_.size() )
				return false;
      return linkLayer_.at( i ).is< T >();
    }

    //!is<some class> returns true if this is of that type 
    //!example: inetIs<IPv4> returns true if IPv4 
    template < class T > bool inetIs( uint32_t i = 0 ) const
    {
			if( i >= inetLayer_.size() )
				return false;
      return inetLayer_.at( i ).is< T >();
    }

    //!is<some class> returns true if this is of that type 
    //!example: transIs<TCP> returns true if TCP
    template < class T > bool transIs( uint32_t i = 0 ) const
    {
			if( i >= transLayer_.size() )
				return false;
      return transLayer_.at( i ).is< T >();
    }

    //!is<some class> returns true if this is of that type 
    //!example: appIs<Raw> returns true if Raw 
    template < class T > bool appIs( uint32_t i = 0 ) const
    {
			if( i >= appLayer_.size() )
				return false;
      return appLayer_.at( i ).is< T >();
    }

    //!Returns the number of objects in the link layer
    int linkSize( ) const;
    //!Returns the number of objects in the inet layer
    int inetSize( ) const;
    //!Returns the number of objects in the transport layer
    int transSize( )const;
    //!Returns the number of objects in the application layer
    int appSize( ) const;

    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: getLink<Ethernet> returns an Ethernet object 
    template < class T > T getLink( int i = 0 ) const 
    { 
      Link l = linkLayer_.at( i );
      return l.get<T>();
    }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: getInet<IPv4> returns an IPv4 object
    template < class T > T getInet( int i = 0 ) const
    { 
      Inet l = inetLayer_.at( i );
      return l.get<T>();
    }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: getTrans<TCP> returns a TCP object
    template < class T > T getTrans( int i = 0 ) const
    { 
      Trans l = transLayer_.at( i );
      return l.get<T>();
    }
    
    //!returns a T object
    //!If this isn't a T object we throw runtime_error
    //!example: getApp<Raw> returns a Raw object
    template < class T > T getApp( int i = 0 ) const
    { 
      App l = appLayer_.at( i );
      return l.get<T>();
    }

    template < class T > void setLink( const T& link, const int index = 0 )
    {
        if( index < linkLayer_.size() )
            linkLayer_[index] = link;
    }

    template < class T > void setInet(const T& inet, const int index = 0 )
    {
        if( index < inetLayer_.size() )
            inetLayer_[index] = inet;
    }

    template < class T > void setTrans( const T& trans, const int index = 0 )
    {
        if( index < transLayer_.size() )
            transLayer_[index] = trans;
    }

    template < class T > void setApp( const T& app, const int index = 0 )
    {
        if( index < appLayer_.size() )
            appLayer_[index] = app;
    }

    void clearLink();
    void clearInet();
    void clearTrans();
    void clearApp();

    //!returns true... overloaded from App
    bool isPacket() const
    {
      return true;
    }

		void setTimestamp( const struct timeval &time );
		struct timeval timestamp( ) const;

  private:
    //!internal data
    std::vector< Link >linkLayer_;
    //!internal data
    std::vector< Inet >inetLayer_;
    //!internal data
    std::vector< Trans >transLayer_;
    //!internal data
    std::vector< App >appLayer_;
    struct timeval timeStamp_;
};

//!Addition of two packets in the same manner as operator+=
Packet operator+( const Packet &l, const Packet &r );

#endif
