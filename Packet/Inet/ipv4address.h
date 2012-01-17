#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include "../packetBuffer.h"
#include <vector>
#include <string>
#include <stdint.h>

class IPv4Address
{
public:
  static const int IPv4AddressSize = 4;
public:
  explicit IPv4Address();
  explicit IPv4Address( uint8_t address[ IPv4AddressSize] );
  explicit IPv4Address( std::vector< uint8_t > address );
  IPv4Address( const uint32_t &ip );
  IPv4Address( const std::string &ip);
  virtual ~IPv4Address();
  bool operator == ( const IPv4Address &ip );
  IPv4Address& operator=( const IPv4Address &ip );
  IPv4Address( const IPv4Address& n );
  void setIPv4Address( const std::vector< uint8_t > &address );
  void setIPv4Address( const uint8_t (&ip)[IPv4AddressSize]);
  void setIPv4Address( const uint32_t &ip );
  void setIPv4Address( const std::string &ip );
  int size() const;
  PacketBuffer makePacket() const;
  uint32_t inAddr() const;
  std::string toString() const;
  IPv4Address operator&( const IPv4Address& address ) const;
  IPv4Address operator|( const IPv4Address& address ) const;
  IPv4Address operator^( const IPv4Address& address ) const;

private:
  uint32_t ip_;

};

#endif // IPV4ADDRESS_H
