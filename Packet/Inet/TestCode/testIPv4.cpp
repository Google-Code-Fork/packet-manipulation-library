#include "../../../Test/QUnit.hpp"
#include "../ipv4.h"
#include <iostream>
#include <netinet/in.h>

class IPv4Test
{
	public:
		IPv4Test( std::ostream &out, int verboseLevel = QUnit::verbose ) : qunit(
				out, verboseLevel)
	{
	}

		int run()
		{
			testIsIpv4();
			testPacketCreation();
			return qunit.errors();
		}

	private:
		QUnit::UnitTest qunit;

		void testIsIpv4()
		{
			IPv4 ipv4;
			QUNIT_IS_TRUE( ipv4.isIPv4() );
		}

		void testPacketCreation()
		{
			//20 bytes IPv4 header taken from a wireshark dump
			uint8_t bits[] = { 0x45, 0x00, 0x00, 0x30, 0x62, 0xd7, 0x40, 0x00, 0x80,
				0x06, 0xf8, 0x7b, 0xa3, 0xf0, 0xa8, 0xe7, 0xc1, 0x6e, 0x91, 0x2e};

			//construct IPv4 header from bytes above
			IPv4 ipv4_1( bits, 20 );

			//copy
			IPv4 ipv4_2( ipv4_1 );
			
			QUNIT_IS_EQUAL( ipv4_1.size(), ipv4_2.size() );

			//pull out destination IP and compare them
			uint32_t destination1 = ipv4_1.destinationAddress();
			uint32_t destination2 = ipv4_2.destinationAddress();
			QUNIT_IS_TRUE( destination1 == destination2);

			//Correct value for the destination address
			uint8_t rightDesinationAddress[] = {0xc1, 0x6e, 0x91, 0x2e};
			uint8_t rightSourceAddress[] = {0xa3, 0xf0, 0xa8, 0xe7};

			//Store the destination address for comparison
			uint32_t destinationAddress[4];
			destination1.destinationAddress( destinationAddress );

		}

};

int main()
{
	return IPv4Test( std::cerr ).run();
}
