/*
 * file IPv6Address.cpp
 * This is the definition for the class for handling IPv6 addresses
*/

#include <stdexcept>
#include "ipv6Address.h"
#include "inetData.h"
#include <arpa/inet.h>
#include "../packetBuffer.h"

IPv6Address::IPv6Address() : address_( std::vector< uint8_t >(16,0) )
{
}

IPv6Address::IPv6Address( const uint8_t address[IPv6AddressSize] ) : address_(
		std::vector< uint8_t >(16,0) )
{
	address_[0] = address[0];
	address_[1] = address[1];
	address_[2] = address[2];
	address_[3] = address[3];
	address_[4] = address[4];
	address_[5] = address[5];
	address_[6] = address[6];
	address_[7] = address[7];
	address_[8] = address[8];
	address_[9] = address[9];
	address_[10] = address[10];
	address_[11] = address[11];
	address_[12] = address[12];
	address_[13] = address[13];
	address_[14] = address[14];
	address_[15] = address[15];
}

IPv6Address::IPv6Address( const std::string &address )
{
  setIPv6Address(address);
}

IPv6Address::IPv6Address( const std::vector< uint8_t > &address ) : address_(
		std::vector< uint8_t >(16,0) )
{
	if( address.size() != 16 )
		throw std::runtime_error( "IPv6 Address Size Incorrect" );
	address_ = address;
}

IPv6Address::IPv6Address( const IPv6Address &a )
{
	address_ = a.address_;
}

IPv6Address& IPv6Address::operator=( const IPv6Address &a )
{
	address_ = a.address_;
	return *this;
}

bool IPv6Address::operator==( const IPv6Address &a )
{
	if( address_[0] != a.address_[0] )
		return false;
	if( address_[1] != a.address_[1] )
		return false;
	if( address_[2] != a.address_[2] )
		return false;
	if( address_[3] != a.address_[3] )
		return false;
	if( address_[4] != a.address_[4] )
		return false;
	if( address_[5] != a.address_[5] )
		return false;
	if( address_[6] != a.address_[6] )
		return false;
	if( address_[7] != a.address_[7] )
		return false;
	if( address_[8] != a.address_[8] )
		return false;
	if( address_[9] != a.address_[9] )
		return false;
	if( address_[10] != a.address_[10] )
		return false;
	if( address_[11] != a.address_[11] )
		return false;
	if( address_[12] != a.address_[12] )
		return false;
	if( address_[13] != a.address_[13] )
		return false;
	if( address_[14] != a.address_[14] )
		return false;
	if( address_[15] != a.address_[15] )
		return false;
	return true;
}

IPv6Address::~IPv6Address()
{
}

void IPv6Address::setIPv6Address( const std::vector< uint8_t > &address )
{
	if( address.size() != 16 )
	{
		throw std::runtime_error( "Invalid IPv6 address!" );
	}
	address_ = address;
}

void IPv6Address::setIPv6Address( const std::string &ip )
{
  unsigned char buf[sizeof(struct in6_addr)];
  int s;

  s = inet_pton(AF_INET6, ip.c_str(), buf);
  if (s <= 0)
  {
      if (s == 0)
          std::cerr <<  "IPv6 Address not in correct format \n" << std::endl;
      else
          std::cerr << "Error: inet_pton" << std::endl;
  }

  address_.clear();

  for( int i = 0; i < 16; ++i )
  {
    address_.push_back( buf[i] );
  }
}

std::string IPv6Address::toString() const
{
  unsigned char buf[sizeof(struct in6_addr)];
  char str[INET6_ADDRSTRLEN];

  for( int i = 0; i < 16; ++i )
  {
    buf[i] = address_[i];
  }

  if( NULL == inet_ntop( AF_INET6, buf, str, INET6_ADDRSTRLEN )) //error
  {
    std::cerr << "Error inet_ntop \n" << std::endl;
  }

  return std::string( str );
}

int IPv6Address::size() const
{
	return IPv6AddressSize;
}

PacketBuffer IPv6Address::makePacket( ) const
{
	return PacketBuffer( address_ );
}

void IPv6Address::ipv6Array( uint8_t (&addressPtr)[IPv6AddressSize] )
{
	addressPtr[0] = address_[0];
	addressPtr[1] = address_[1];
	addressPtr[2] = address_[2];
	addressPtr[3] = address_[3];
	addressPtr[4] = address_[4];
	addressPtr[5] = address_[5];
	addressPtr[6] = address_[6];
	addressPtr[7] = address_[7];
	addressPtr[8] = address_[8];
	addressPtr[9] = address_[9];
	addressPtr[10] = address_[10];
	addressPtr[11] = address_[11];
	addressPtr[12] = address_[12];
	addressPtr[13] = address_[13];
	addressPtr[14] = address_[14];
	addressPtr[15] = address_[15];
}

bool IPv6Address::isIPv6() const
{
	return true;
}

IPv6Address IPv6Address::operator &(const IPv6Address& address) const
{
  std::vector< uint8_t > bytes;
  for( int i = 0; i < IPv6AddressSize; ++i )
  {
    bytes.push_back( address_[i] & address.address_[i] );
  }
  return IPv6Address( bytes );
}

IPv6Address IPv6Address::operator |(const IPv6Address& address) const
{
  std::vector< uint8_t > bytes;
  for( int i = 0; i < IPv6AddressSize; ++i )
  {
    bytes.push_back( address_[i] | address.address_[i] );
  }
  return IPv6Address( bytes );
}

IPv6Address IPv6Address::operator ^(const IPv6Address& address) const
{
  std::vector< uint8_t > bytes;
  for( int i = 0; i < IPv6AddressSize; ++i )
  {
    bytes.push_back( address_[i] ^ address.address_[i] );
  }
  return IPv6Address( bytes );
}
