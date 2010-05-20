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
		UdpTest( std::ostream &out, int verboseLevel = QUnit::verbose ); 
		
		int run();

	private:
		QUnit::UnitTest qunit;

		void testConstruction();
};

