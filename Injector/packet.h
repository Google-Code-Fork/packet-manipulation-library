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

class Packet : public AppData
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
    int getSize() const;
   
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
      Inet l = inetLayer_.at( i );
      return l.get<T>();
    }
    
    template < class T > T getTrans( int i ) const
    { 
      Trans l = transLayer_.at( i );
      return l.get<T>();
    }
    
    template < class T > T getApp( int i ) const
    { 
      App l = appLayer_.at( i );
      return l.get<T>();
    }

    bool isPacket() const
    {
      return true;
    }

  private:
    std::vector< Link > linkLayer_;
    std::vector< Inet > inetLayer_;
    std::vector< Trans > transLayer_;
    std::vector< App > appLayer_;
};

Packet operator+( const Packet &l, const Packet &r );

#endif
