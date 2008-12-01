#ifndef PACKET_H
#define PACKET_H

#include "encapsulateable.h"
#include "Link/link.h"
#include "App/app.h"
#include "Inet/inet.h"
#include "Trans/trans.h"

template< class T > class Packet : public Encapsulateable
{
  public:
    Packet();
    Packet( std::vector< uint8_t > data );
    Packet~();

    std::vector< uint8_t > makePacket();
    void pushBackLink( Link l );
    void pushBackInet( Inet i );
    void pushBackTrans( Trans t );
    void pushBackApp( App a );

    int linkSize( );
    int InetSize( );
    int TransSize( );
    int AppSize( );

    Link getLink( int i );
    Inet getInet( int i );
    Trans getTrans( int i );
    App getApp( int i );

  private:
    std::vector< Link > linkLayer;
    std::vector< Inet > inetLayer;
    std::vector< Trans > transLayer;
    std::vector< App > appLayer;
}
#endif
