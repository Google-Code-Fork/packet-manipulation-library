#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "packet.h"
#include "Link/ethernet.h"
#include "Inet/ipv4.h"
#include "Trans/tcp.h"
#include "Trans/udp.h"
#include "App/raw.h"

class PacketBuilder
{
  public:
  PacketBuilder(  ) {}
  virtual ~PacketBuilder(){}

  template <class T> Packet buildPacket( PacketBuffer pb ) { return build< T >( pb.getBuffer(), pb.size() ); }
  template <class K> Packet build( const uint8_t* buff, int size );
};

//template specialization must go outside of class def
template <> Packet PacketBuilder::build<Raw>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<UDP>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<TCP>( const  uint8_t* buff, int size );
template <> Packet PacketBuilder::build<Ethernet>( const uint8_t* buff, int size );
template <> Packet PacketBuilder::build<IPv4>( const uint8_t* buff, int size );
#endif
