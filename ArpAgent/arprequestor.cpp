#include "arprequestor.h"
#include "../Packet/packet.h"

ArpRequestor::ArpRequestor()
{
}

ArpRequestor::~ArpRequestor()
{
}

void ArpRequestor::setDevice(const std::string device)
{
  MutexLocker lock( injectorMutex_ );
  injector_.setDevice( device );
}

std::string ArpRequestor::device() const
{
  MutexLocker lock( injectorMutex_ );
  return injector_.device();
}

void ArpRequestor::setSourceMAC(const MACAddress &mac)
{
  MutexLocker lock( injectorMutex_ );
  mac_ = mac;
}

MACAddress ArpRequestor::sourceMac()const
{
  MutexLocker lock( injectorMutex_ );
  return mac_;
}

void ArpRequestor::setSourceIP(const IPv4Address &ip)
{
  MutexLocker lock( injectorMutex_ );
  ip_ = ip;
}

IPv4Address ArpRequestor::sourceIP() const
{
  MutexLocker lock( injectorMutex_ );
  return ip_;
}

void ArpRequestor::arp( const IPv4Address &dest )
{
  MutexLocker lock( injectorMutex_ );
  Packet p;
  Ethernet ether;
  MACAddress dmac;
  dmac.setMACAddress( std::vector<uint8_t>(6, 0xFF) );//Broadcast
  ether.setSourceMAC( mac_ );
  dmac.setMACAddress( std::vector< uint8_t >( 6, 0x00 ) );//Zero'd

  //ether.setType( ethernetProtocol::ETH_P_ARP  );

  Arp arp;
  arp.setHardwareSize( hardwaresize::ETHERNET );
  arp.setProtocolSize( protocolsize::IP );
  arp.setProtocolType( protocoltype::IP );
  arp.setOpcode( arpopcode::request );
  arp.setSenderIPAddress( ip_.makePacket() );
  arp.setSenderMacAddress( mac_.makePacket() );
  arp.setTargetIPAddress( dest.makePacket() );
  arp.setTargetMacAddress( dmac.makePacket() );
  p.pushBackLink( ether );
  p.pushBackApp( arp );
  injector_.inject( p );

}
