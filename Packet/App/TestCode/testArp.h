#include "../../../Test/QUnit.hpp"
#include "../arp.h"
#include <iostream>
#include <netinet/in.h>

class ARPTest
{
	public:
		ARPTest( std::ostream &out, int verboseLevel = QUnit::verbose );

		int run();

	private:
		QUnit::UnitTest qunit;

		void testIsARP();

		void testConstruction();
};

