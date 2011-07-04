#include "ipv4address.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>

IPv4Address::IPv4Address():ip_(0)
{
}

IPv4Address::IPv4Address( uint8_t address[ IPv4AddressSize ] )
{
  ip_ = address[0] << 24;
  ip_ |= address[1] << 16;
  ip_ |= address[2] << 8;
  ip_ |= address[3];
}

IPv4Address::IPv4Address( std::vector< uint8_t > address )
{
  if( address.size() < 4)
    ip_ = 0;
  else
  {
    ip_ = address[0] << 24;
    ip_ |= address[1] << 16;
    ip_ |= address[2] << 8;
    ip_ |= address[3];
  }
}

IPv4Address::IPv4Address( const uint32_t &ip ): ip_( ip )
{
}

IPv4Address::IPv4Address( const std::string &ip )
{
  int err = inet_aton( ip.c_str(), ((in_addr*)(&ip_)));
  if( err )
    ip_ = 0;
  ip_ = ntohl( ip_ );
}

IPv4Address::~IPv4Address()
{
}

bool IPv4Address::operator==( const IPv4Address &ip )
{
  return ip_ == ip.ip_;
}

IPv4Address& IPv4Address::operator=( const IPv4Address& ip )
{
  ip_ = ip.ip_;
  return *this;
}

IPv4Address::IPv4Address( const IPv4Address &n )
{
  ip_ = n.ip_;
}

void IPv4Address::setIPv4Address(const std::string &ip)
{
  int err = inet_aton( ip.c_str(), ((in_addr*)(&ip_)));
  if( err )
    ip_ = 0;
  ip_ = ntohl( ip_ );
}

void IPv4Address::setIPv4Address(const std::vector<uint8_t> &address)
{
  if( address.size() < 4 )
    ip_ = 0;
  else
  {
    ip_ = address[0] << 24;
    ip_ |= address[1] << 16;
    ip_ |= address[2] << 8;
    ip_ |= address[3];
  }
}

void IPv4Address::setIPv4Address( const uint32_t &ip)
{
  ip_ = htonl(ip);
}

void IPv4Address::setIPv4Address( const uint8_t (&address)[IPv4AddressSize])
{
  ip_ = address[0] << 24;
  ip_ |= address[1] << 16;
  ip_ |= address[2] << 8;
  ip_ |= address[3];
}

int IPv4Address::size() const
{
  return IPv4AddressSize;
}

PacketBuffer IPv4Address::makePacket() const
{
  std::vector< uint8_t > buff;
  buff.push_back( static_cast< uint8_t >( ip_ >> 24 ) );
  buff.push_back( static_cast< uint8_t >( (ip_ & 0x00FF0000) >> 16 ) );
  buff.push_back( static_cast< uint8_t >( (ip_ & 0x0000FF00) >> 8 ) );
  buff.push_back( static_cast< uint8_t >( ip_ & 0x000000ff) );
  PacketBuffer pb;
  pb.setBuffer(buff);
  return pb;
}

uint32_t IPv4Address::inAddr() const
{
  return ntohl(ip_);
}

std::string IPv4Address::toString() const
{
  uint32_t address = htonl( ip_ );
  const uint8_t *octet = reinterpret_cast< uint8_t* >( &address );
  std::stringstream ss;
  ss << static_cast< uint16_t >( octet[0] ) << ".";
  ss << static_cast< uint16_t >( octet[1] ) << ".";
  ss << static_cast< uint16_t >( octet[2] ) << ".";
  ss << static_cast< uint16_t >( octet[3] );
  return ss.str();
}
