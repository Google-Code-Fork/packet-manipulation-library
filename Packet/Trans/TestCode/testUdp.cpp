#include "../../../Test/QUnit.hpp"
#include "../udp.h"
#include <iostream>
#include <netinet/in.h>

/*
 * UDP used taken from Wireshark
 * Source Port: 54555
 * Dest Port: 53
 * Length: 39
 * Checksum: 0x4b15
*/

class UdpTest
{
	public:
		UdpTest( std::ostream &out, int verboseLevel = QUnit::verbose ) : qunit(
				out, verboseLevel)
		{
		}

		int run()
		{
			testConstruction();
			return qunit.errors();
		}

	private:
		QUnit::UnitTest qunit;

		void testConstruction()
		{
			//8 bytes UDP header taken from wireshark dump
			uint8_t bits[] = { 0xd5, 0x1b, 0x00, 0x35, 0x00, 0x27, 0x4b, 0x15 };

			//construct UDP header from bytes above
			UDP udp1( bits, 8 );

			//copy UDP header
			UDP udp2( udp1 );

			//check source port
			QUNIT_IS_TRUE( udp1.sourcePort() == 0xd51b );
			//check set source port
			udp1.setSourcePort( 0xd599 );
			QUNIT_IS_TRUE( udp1.sourcePort() == 0xd599 );

			//check dest port
			QUNIT_IS_TRUE( udp1.destinationPort() == 0x0035 );
			//check set dest source port
			udp1.setDestinationPort( 0x1111 );
			QUNIT_IS_TRUE( udp1.destinationPort() == 0x1111 );

			//check checksum
			QUNIT_IS_TRUE( udp1.checksum() == 0x4b15 );
			//check set checksum
			udp1.setChecksum( 0x4b11 );
			QUNIT_IS_TRUE( udp1.checksum() == 0x4b11 );

			//check length
			QUNIT_IS_TRUE( udp1.length() == 0x0027 );
			//set length
			udp1.setLength( 0x0030 );
			QUNIT_IS_TRUE( udp1.length() == 0x0030 );

			//check size
			QUNIT_IS_TRUE( udp1.size() == 8 );
			QUNIT_IS_EQUAL( udp1.size(), udp2.size() );

			//check if UDP header
			QUNIT_IS_TRUE( udp1.isUDP() );
		}
};

int main()
{
	return UdpTest( std::cerr ).run();
}
