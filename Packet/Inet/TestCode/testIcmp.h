#include "../../../Test/QUnit.hpp"
#include "../icmp.h"
#include <iostream>
#include <netinet/in.h>

/*
 * Type: 8 (Echo Request)
 * Code: 0
 * Checksum: 0x8c53
 * Identifier: 0x0200
 * Sequence number: 48904 (0xbf08)
 * Data: (32 bytes)
*/

class IcmpTest
{
	public:
		IcmpTest( std::ostream &out, int verboseLevel = QUnit::verbose );
		
		int run();

	private:
		QUnit::UnitTest qunit;

		void testIsIcmp();

		void testConstruction();
};
