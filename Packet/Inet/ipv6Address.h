/*
 * class IPv6Address.h
 * This class is used in conjunction with IPv6 for handling IPv6 addresses
*/

#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

#include <string>
#include <vector>
#include "inetData.h"
#include "../packetBuffer.h"

class IPv6Address : public InetData
{
	public: //constants
		//! Size of a IPv6 address in bytes
		static const int IPv6AddressSize = 16;

	public:
		//! Default Constructor
		IPv6Address();
		//! Builds a IPv6Address with the bytes in IPv6
    IPv6Address( const uint8_t address[IPv6AddressSize] );
		//! Builds a IPv6Address with the bytes in IPv6
    IPv6Address( const std::vector< uint8_t > &address );
    //! Builds a IPv6Address from a string
    IPv6Address( const std::string &address );
		//! Copy Constructor
		IPv6Address( const IPv6Address& a );
		//! Assignment operator
		IPv6Address& operator=( const IPv6Address &a );
		//! Equality operation
    bool operator == ( const IPv6Address &a );
    IPv6Address operator&( const IPv6Address& address ) const;
    IPv6Address operator|( const IPv6Address& address ) const;
    IPv6Address operator^( const IPv6Address& address ) const;

		//! Destructor
		virtual ~IPv6Address();
		
		//! Sets the address base on the bytes in IPv6
    void setIPv6Address( const std::vector< uint8_t > &address );
    void setIPv6Address( const std::string &ip );
		//! Returns the size of the IPv6 address
		int size() const;
		//! Returns a Packetbuffer with the IPv6 address
		PacketBuffer makePacket() const;
		//! Places the IPv6 address in the array IPv6
		void ipv6Array( uint8_t (&address) [IPv6AddressSize]);
		//! returns true
    bool isIPv6() const;
    std::string toString() const;

	private:
		//! Private data of IPv6Address
		std::vector< uint8_t > address_;
};

#endif
