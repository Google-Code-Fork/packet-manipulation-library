#ifndef PACKET_H
#define PACKET_H

#include "encapsulateable.h"
#include "packetBuffer.h"
#include "Link/linkData.h"
#include "App/appData.h"
#include "Inet/inetData.h"
#include "Trans/transData.h"
#include <vector>
#include <stdexcept>

class Packet : public Encapsulateable
{
  public:
    Packet();
//    Packet( PacketBuffer packet );
//    Packet( std::vector< uint8_t > data );
    Packet( const Packet &n );
    Packet& operator=( const Packet &n );
    ~Packet();
    Packet& operator+=( const Packet &n );

    PacketBuffer makePacket() const;
    template<class T> void pushBackLink( T l )
    {
      linkLayer_.push_back( l );
    }

    template<class T> void pushBackInet( T i )
    {
      inetLayer_.push_back( i );
    }

    template<class T > void pushBackTrans( T t )
    {
      transLayer_.push_back( t );
    }

    template < class T > void pushBackApp( T a )
    {
      appLayer_.push_back( a );
    }

    int linkSize( ) const;
    int inetSize( ) const;
    int transSize( )const;
    int appSize( ) const;

    template < class T > T getLink( int i ) const 
    { 
      Link l = linkLayer_.at( i );
      return l.get<T>();
    }
    
    template < class T > T getInet( int i ) const
    { 
      InetData l = inetLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }
    
    template < class T > T getTrans( int i ) const
    { 
      TransData l = transLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }
    
    template < class T > T getApp( int i ) const
    { 
      AppData l = appLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }

  private:
    std::vector< Link > linkLayer_;
    std::vector< InetData* > inetLayer_;
    std::vector< TransData* > transLayer_;
    std::vector< AppData* > appLayer_;
};
#endif
