#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "packet.h"
#include "Link/ethernet.h"
#include "Inet/ipv4.h"
#include "Trans/tcp.h"
#include "Trans/udp.h"
#include "App/raw.h"

template <class T > class PacketBuilder
{
  PacketBuilder(  ) {}
  virtual ~PacketBuilder();

  Packet buildPacket( PacketBuffer pb ) { return build< T >( pb.getBuffer(), pb.size() ); }
  template <class K> Packet build( const uint8_t* buff, int size );
}

//template specialization must go outside of class def
template <> Packet PacketBuilder::build<Ethernet>( const uint8_t* buff, int size )
{
  Ethernet e( buff, size );
  Packet p;
  p.pushBackLink( e );
  uint8_t* newbuff = buff + e.getSize();
  int newsize = size - e.getSize();
  Packet p2;
  switch( e.getType() )
  {
    case ethernetProtocol::ETH_P_IP:
      p2 = build< IPv4 >( newbuff, newsize );
      break;
    case ethernetProtocol::ETH_P_IPV6:
      //placeholder
      //break;
    case ethernetProtocol::ETH_P_ARP:
      //placeholder
      //break;
    default:
      p2 = build< Raw >( newbuff, newsize );
      break;
  }
  return p + p2;
}

template <> Packet PacketBuilder::build<IPv4>( const uint8_t* buff, int size )
{
  IPv4 ip( buff, size );
  Packet p; 
  p.pushBackInet( ip );
  Packet p2;
  uint8_t* newbuff = buff + p.getSize();
  int newsize = size - p.getSize();
  
  switch( static_cast<uint16_t>( ip.getProtocol() ) )
  {
    case ipProtocols::IPPROTO_TCP:
      p2 = build< TCP >( newbuff, newsize );
      break;
    case ipProtocols::IPPROTO_UDP:
      p2 = build< TCP >( newbuff, newsize );
      break;
    default:
      p2 = build< Raw >( newbuff, newsize );
  }

  return p + p2;
}

template <> Packet PacketBuilder::build<TCP>( const  uint8_t* buff, int size )
{
  TCP tcp( buff, size );
  Packet p; 
  p.pushBackTrans( tcp );
  Packet p2;
  uint8_t* newbuff = buff + tcp.getSize();
  int newsize = size - tcp.getSize();

  //NO TCP APPLICATION LAYER SUPPORTED ATM
  p2 = build< Raw >( newbuff, newsize );

  return p + p2;
}

template <> Packet PacketBuilder::build<UDP>( const  uint8_t* buff, int size )
{
  UDP udp( buff, size );
  Packet p; 
  p.pushBackTrans( udp );
  Packet p2;
  uint8_t* newbuff = buff + udp.getSize();
  int newsize = size - udp.getSize();

  //NO UDP APPLICATION LAYER SUPPORTED ATM
  p2 = build< Raw >( newbuff, newsize );

  return p + p2;
}

template <> Packet PacketBuilder::build<Raw>( const  uint8_t* buff, int size )
{
  Raw r( buff, size );
  Packet p;
  p.pushBackApp( r );

  return p;
}

#endif
