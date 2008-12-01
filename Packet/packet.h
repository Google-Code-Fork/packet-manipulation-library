#ifndef PACKET_H
#define PACKET_H

#include "encapsulateable.h"
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

    std::vector< uint8_t > makePacket();
    void pushBackLink( LinkData l );
    void pushBackInet( InetData i );
    void pushBackTrans( TransData t );
    void pushBackApp( AppData a );

    int linkSize( );
    int inetSize( );
    int transSize( );
    int appSize( );

    template < class T > T getLink( int i ) 
    { 
      LinkData l = linkLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }
    
    template < class T > T getInet( int i )
    { 
      InetData l = inetLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }
    
    template < class T > T getTrans( int i )
    { 
      TransData l = transLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }
    
    template < class T > T getApp( int i )
    { 
      AppData l = appLayer_.at( i );
      if(!( l.is< T >()) )
	throw std::runtime_error( "not the right type" );
      return static_cast< T >( l );
    }

  private:
    std::vector< LinkData > linkLayer_;
    std::vector< InetData > inetLayer_;
    std::vector< TransData > transLayer_;
    std::vector< AppData > appLayer_;
};
#endif
