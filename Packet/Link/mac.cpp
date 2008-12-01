#include <stdexcept>
#include "mac.h"

MACAddress::MACAddress() : mac_( std::vector< uint8_t >(6,0) )
{
}

MACAddress::MACAddress( uint8_t mac[MACAddressSize] ) : mac_( std::vector< uint8_t >(6,0) )
{
  mac_[0] = mac[0];
  mac_[1] = mac[1];
  mac_[2] = mac[2];
  mac_[3] = mac[3];
  mac_[4] = mac[4];
  mac_[5] = mac[5];
}

MACAddress::MACAddress( std::vector< uint8_t > mac ) : mac_( std::vector< uint8_t >(6,0) )
{
  if( mac.size() != 6 )
    throw std::runtime_error( "Mac Address Size Incorrect" );
  mac_ = mac;
}

MACAddress::MACAddress( const MACAddress &a ) 
{
  mac_ = a.mac_; 
}

MACAddress& MACAddress::operator=( const MACAddress &a )
{
  mac_ = a.mac_;
  return *this;
}

MACAddress::~MACAddress()
{
}

void MACAddress::setMACAddress( std::vector< uint8_t > mac )
{
  if( mac.size() != 6 )
  {
    throw std::runtime_error( "Invalid MAC address" );
  }
  mac_ = mac;
}

int MACAddress::getSize()
{
  return MACAddressSize;
}

std::vector< uint8_t > MACAddress::makePacket(  )
{
  return mac_;
}

void MACAddress::getMAC( uint8_t (&macPtr)[MACAddressSize] )
{
  macPtr[0] = mac_[0];
  macPtr[1] = mac_[1];
  macPtr[2] = mac_[2];
  macPtr[3] = mac_[3];
  macPtr[4] = mac_[4];
  macPtr[5] = mac_[5];
}
