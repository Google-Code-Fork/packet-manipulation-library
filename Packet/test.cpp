#include "packetBuilder.h"
#include <iostream>

int main()
{
  Ethernet e;
  IPv4 ip;
  TCP tcp;
  Raw raw;
  Packet p;
  e.setType( ethernetProtocol::ETH_P_IP );
  p.pushBackLink( e );
  ip.setProtocol( ipProtocols::IPPROTO_TCP );
  p.pushBackInet( ip );
  p.pushBackTrans( tcp );
  std::vector< uint8_t > data( 100 );
  raw.setData( data );
  p.pushBackApp( raw );

  //TEST getting the byte buffer associated with packet p;
  PacketBuffer packBuff;
  packBuff = p.makePacket();

  //Test building packet with a packet buffer
  PacketBuilder pb;
  Packet p2 = pb.buildPacket<Ethernet>( packBuff );

  std::cout << "p2.size(): " << p2.getSize() << std::endl;
  std::cout << "p.size(): " << p.getSize() << std::endl;
  std::cout << "packetBuff.size(): " << packBuff.size() << std::endl;

  std::cout << "p is " <<  (p.linkIs<Ethernet>( 0 ) ? "Ethernet" : "Not Ethernet" ) << std::endl;
  std::cout << "p2 is " << (p2.linkIs<Ethernet>( 0 ) ? "Ethernet" : "Not Ethernet" ) << std::endl;

  

  return 0;
}
